#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$ROOT_DIR/smart_inventory_test"

cleanup() {
  rm -f "$BIN"
}
trap cleanup EXIT

g++ -std=c++17 -Wall -Wextra -pedantic -I"$ROOT_DIR/include" "$ROOT_DIR"/src/*.cpp -o "$BIN"

total_tests=0
passed_tests=0

record_pass() {
  local label="$1"

  total_tests=$((total_tests + 1))
  passed_tests=$((passed_tests + 1))
  echo "PASS: $label"
}

record_fail() {
  local label="$1"
  local detail="$2"

  total_tests=$((total_tests + 1))
  echo "FAIL: $label"
  echo "$detail"
}

assert_contains() {
  local output="$1"
  local expected="$2"
  local label="$3"

  if [[ "$output" != *"$expected"* ]]; then
    record_fail "$label" "Expected to find: $expected"
    return
  fi
  record_pass "$label"
}

assert_not_contains() {
  local output="$1"
  local unexpected="$2"
  local label="$3"

  if [[ "$output" == *"$unexpected"* ]]; then
    record_fail "$label" "Did not expect to find: $unexpected"
    return
  fi
  record_pass "$label"
}

assert_equals() {
  local actual="$1"
  local expected="$2"
  local label="$3"

  if [[ "$actual" != "$expected" ]]; then
    record_fail "$label" "Expected: $expected, got: $actual"
    return
  fi
  record_pass "$label"
}

employee_view_output="$(printf '1\n1\nemployee\nemp123\n1\n0\n0\n' | "$BIN")"
assert_contains "$employee_view_output" "=== Employee Menu ===" "employee reaches employee menu"
assert_contains "$employee_view_output" "ID: I1001 | Name: Apple" "employee can view inventory"
assert_contains "$employee_view_output" "ID: I1004 | Name: Bread" "employee view shows all seeded items"

employee_search_output="$(printf '1\n1\nemployee\nemp123\n2\napp\n2\ni1003\n2\nunknown\n0\n0\n' | "$BIN")"
assert_contains "$employee_search_output" "ID: I1001 | Name: Apple" "employee search is case-insensitive by name"
assert_contains "$employee_search_output" "ID: I1003 | Name: Milk" "employee search is case-insensitive by item id"
assert_contains "$employee_search_output" "No item found." "employee search reports no matches"

invalid_login_output="$(printf '1\n1\nemployee\nwrongpass\n0\n' | "$BIN")"
assert_contains "$invalid_login_output" "Authentication failed." "bad credentials are rejected"

signup_output="$(printf '2\n1\nnewemp\npass\n1\n1\nnewemp\npass\n0\n2\n2\nnewmgr\npass\n1\n2\nnewmgr\npass\n0\n0\n' | "$BIN")"
assert_contains "$signup_output" "Employee account created. Employee ID: E-101" "employee signup works"
assert_contains "$signup_output" "Manager account created. Manager ID: M-101" "manager signup works"
assert_contains "$signup_output" "=== Employee Menu ===" "signed-up employee can log in"
assert_contains "$signup_output" "=== Manager Menu ===" "signed-up manager can log in"

signup_validation_output="$(printf '2\n1\n\n2\n1\nemployee\n2\n1\nunique\n\n0\n' | "$BIN")"
assert_contains "$signup_validation_output" "Username cannot be empty." "signup rejects empty usernames"
assert_contains "$signup_validation_output" "Username already exists." "signup rejects duplicate usernames"
assert_contains "$signup_validation_output" "Password cannot be empty." "signup rejects empty passwords"

manager_employee_ops_output="$(printf '1\n2\nmanager\nadmin123\n2\nMilk\n3\nI1003\n1\n0\n0\n' | "$BIN")"
assert_contains "$manager_employee_ops_output" "=== Manager Menu ===" "manager reaches manager menu"
assert_contains "$manager_employee_ops_output" "ID: I1003 | Name: Milk" "manager can use inherited search"
assert_contains "$manager_employee_ops_output" "Transaction recorded successfully." "manager can use inherited transaction"

invalid_transaction_output="$(printf '1\n1\nemployee\nemp123\n3\nBADID\n1\n3\nI1001\n999\n0\n0\n' | "$BIN")"
assert_contains "$invalid_transaction_output" "Item not found." "transaction rejects missing item ids"
assert_contains "$invalid_transaction_output" "Invalid quantity for transaction." "transaction rejects quantities above stock"

manager_inventory_ops_output="$(printf '1\n2\nmanager\nadmin123\n4\nOrange\nProduce\n12\n1.25\n4\n2\nOrange\n7\nI1005\nOrange Juice\nBeverage\n2.50\n3\n2\nOrange Juice\n8\nI1005\n30\n2\nOrange Juice\n5\nI1005\n2\nOrange Juice\n5\nBADID\n0\n0\n' | "$BIN")"
assert_contains "$manager_inventory_ops_output" "Item added." "manager can add an item"
assert_contains "$manager_inventory_ops_output" "ID: I1005 | Name: Orange" "added item is searchable"
assert_contains "$manager_inventory_ops_output" "Item details updated successfully." "manager can update item details"
assert_contains "$manager_inventory_ops_output" "ID: I1005 | Name: Orange Juice | Category: Beverage | Qty: 12 | Price: \$2.50 | Threshold: 3" "updated item details are shown"
assert_contains "$manager_inventory_ops_output" "Stock quantity updated." "manager can update stock quantity"
assert_contains "$manager_inventory_ops_output" "ID: I1005 | Name: Orange Juice | Category: Beverage | Qty: 30 | Price: \$2.50 | Threshold: 3" "updated stock quantity is shown"
assert_contains "$manager_inventory_ops_output" "Item deleted successfully." "manager can delete an item"
assert_contains "$manager_inventory_ops_output" "Failed to delete item." "manager gets feedback when deleting a missing item"
assert_not_contains "${manager_inventory_ops_output##*Item deleted successfully.}" "ID: I1005 | Name: Orange Juice" "deleted item no longer appears in later search"

manager_low_stock_output="$(printf '1\n2\nmanager\nadmin123\n6\n0\n0\n' | "$BIN")"
assert_contains "$manager_low_stock_output" "ID: I1002 | Name: Banana" "low-stock report includes Banana"
assert_contains "$manager_low_stock_output" "ID: I1004 | Name: Bread" "low-stock report includes Bread"

initial_restock_output="$(printf '1\n2\nmanager\nadmin123\n9\n0\n0\n' | "$BIN")"
assert_contains "$initial_restock_output" "No restock requests." "new session starts with no pending restock requests"

missing_restock_output="$(printf '1\n2\nmanager\nadmin123\n9\n1\nI1001\n0\n0\n' | "$BIN")"
assert_contains "$missing_restock_output" "No restock requests." "review handles an empty restock queue"
assert_contains "$missing_restock_output" "No restock request found for this item." "fulfill reports missing restock request"

restock_output="$(printf '1\n1\nemployee\nemp123\n3\nI1001\n11\n0\n1\n2\nmanager\nadmin123\n9\n1\nI1001\n0\n0\n' | "$BIN")"
assert_contains "$restock_output" "Request R1 | item I1001 | req qty 11" "low-stock sale creates restock request"
assert_contains "$restock_output" "Restock fulfilled. New qty: 20" "manager can fulfill restock request"
assert_not_contains "${restock_output##*Restock fulfilled. New qty: 20}" "Request R1 | item I1001" "fulfilled restock request is cleared"

duplicate_output="$(printf '1\n1\nemployee\nemp123\n3\nI1002\n1\n3\nI1002\n1\n0\n1\n2\nmanager\nadmin123\n9\n0\n0\n' | "$BIN")"
request_count="$(grep -o 'Request R[0-9]' <<< "$duplicate_output" | wc -l | tr -d ' ')"
assert_equals "$request_count" "1" "duplicate restock requests are not created"

input_validation_output="$(printf 'abc\n0\n' | "$BIN")"
assert_contains "$input_validation_output" "Invalid integer input." "main menu rejects non-integer choices"

closed_input_output="$(printf '1\n' | "$BIN")"
assert_contains "$closed_input_output" "Input closed." "closed input exits cleanly"

pass_rate=$((passed_tests * 100 / total_tests))
echo "CLI regression pass rate: $passed_tests/$total_tests (${pass_rate}%)"

if [[ "$pass_rate" -lt 95 ]]; then
  echo "FAIL: pass rate below 95%"
  exit 1
fi

if [[ "$passed_tests" -ne "$total_tests" ]]; then
  echo "FAIL: some CLI regression tests failed"
  exit 1
fi

echo "All CLI regression tests passed."
