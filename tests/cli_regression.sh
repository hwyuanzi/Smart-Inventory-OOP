#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT_DIR/smart_inventory_test"

cleanup() {
  rm -f "$BIN"
}
trap cleanup EXIT

g++ -std=c++17 -Wall -Wextra -pedantic -I"$ROOT_DIR/include" "$ROOT_DIR"/src/*.cpp -o "$BIN"

assert_contains() {
  local output="$1"
  local expected="$2"
  local label="$3"

  if [[ "$output" != *"$expected"* ]]; then
    echo "FAIL: $label"
    echo "Expected to find: $expected"
    exit 1
  fi
}

employee_view_output="$(printf '1\n1\nemployee\nemp123\n1\n0\n0\n' | "$BIN")"
assert_contains "$employee_view_output" "=== Employee Menu ===" "employee reaches employee menu"
assert_contains "$employee_view_output" "ID: I1001 | Name: Apple" "employee can view inventory"

signup_output="$(printf '2\n1\nnewemp\npass\n1\n1\nnewemp\npass\n0\n2\n2\nnewmgr\npass\n1\n2\nnewmgr\npass\n0\n0\n' | "$BIN")"
assert_contains "$signup_output" "Employee account created. Employee ID: E-101" "employee signup works"
assert_contains "$signup_output" "Manager account created. Manager ID: M-101" "manager signup works"
assert_contains "$signup_output" "=== Employee Menu ===" "signed-up employee can log in"
assert_contains "$signup_output" "=== Manager Menu ===" "signed-up manager can log in"

manager_employee_ops_output="$(printf '1\n2\nmanager\nadmin123\n2\nMilk\n3\nI1003\n1\n0\n0\n' | "$BIN")"
assert_contains "$manager_employee_ops_output" "=== Manager Menu ===" "manager reaches manager menu"
assert_contains "$manager_employee_ops_output" "ID: I1003 | Name: Milk" "manager can use inherited search"
assert_contains "$manager_employee_ops_output" "Transaction recorded successfully." "manager can use inherited transaction"

restock_output="$(printf '1\n1\nemployee\nemp123\n3\nI1001\n11\n0\n1\n2\nmanager\nadmin123\n9\n1\nI1001\n0\n0\n' | "$BIN")"
assert_contains "$restock_output" "Request R1 | item I1001 | req qty 11" "low-stock sale creates restock request"
assert_contains "$restock_output" "Restock fulfilled. New qty: 20" "manager can fulfill restock request"

duplicate_output="$(printf '1\n1\nemployee\nemp123\n3\nI1002\n1\n3\nI1002\n1\n0\n1\n2\nmanager\nadmin123\n9\n0\n0\n' | "$BIN")"
request_count="$(grep -o 'Request R[0-9]' <<< "$duplicate_output" | wc -l | tr -d ' ')"
if [[ "$request_count" -ne 1 ]]; then
  echo "FAIL: duplicate restock request prevention"
  echo "Expected 1 pending request, got $request_count"
  exit 1
fi

closed_input_output="$(printf '1\n' | "$BIN")"
assert_contains "$closed_input_output" "Input closed." "closed input exits cleanly"

echo "All CLI regression tests passed."
