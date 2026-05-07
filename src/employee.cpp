#include "employee.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * Timestamp format shared by transactions and restock requests.
 */
namespace
{
    std::string nowTimestamp()
    {
        const time_t now = time(nullptr);
        tm local = *localtime(&now);
        ostringstream stream;
        stream << put_time(&local, "%Y-%m-%d %H:%M:%S");
        return stream.str();
    }
}

/*
 * Employees use the base User login fields plus their staff ID.
 */
Employee::Employee(const string &username, const string &password, const string &employeeId)
    : User(username, password, "employee"), employeeId(employeeId) {}

/*
 * Print the current inventory, keeping the empty case explicit.
 */
void Employee::viewInventory(Inventory &inventory) const
{
    vector<Item> &items = inventory.getAllItems();
    if (items.empty())
    {
        cout << "Inventory is empty.\n";
        return;
    }
    for (const Item &item : items)
    {
        cout << item.toString() << '\n';
    }
}

/*
 * Let Inventory own the actual search rules.
 */
vector<Item *> Employee::searchItem(Inventory &inventory, const string &query) const
{
    return inventory.searchByName(query);
}

/*
 * Record a sale, update stock, and queue a restock request if the sale
 * leaves the item at or below its threshold.
 */
bool Employee::makeTransaction(Inventory &inventory, vector<Transaction> &transactions, const string &id, int qty, string &msg) const
{
    Item *item = inventory.findItem(id);
    if (item == nullptr)
    {
        msg = "Item not found.";
        return false;
    }
    if (qty <= 0 || qty > item->getQuantity())
    {
        msg = "Invalid quantity for transaction.";
        return false;
    }

    const double total = item->getPrice() * static_cast<double>(qty);
    if (!inventory.updateStockQuantity(id, item->getQuantity() - qty))
    {
        msg = "Unable to update stock quantity.";
        return false;
    }

    /*
     * Request enough stock to bring the item back to about twice its threshold.
     */
    if (item->isLowStock())
    {
        const int requestQty = max(1, item->getThreshold() * 2 - item->getQuantity());
        inventory.addRestockRequest(RestockRequest(
            inventory.generateRestockId(),
            item->getItemId(),
            item->getName(),
            item->getQuantity(),
            requestQty,
            nowTimestamp()));
    }

    /*
     * Keep the completed sale in memory for this run.
     */
    transactions.emplace_back(
        "T" + to_string(static_cast<int>(transactions.size()) + 1),
        id,
        item->getName(),
        qty,
        total,
        nowTimestamp());

    msg = "Transaction recorded successfully.";
    return true;
}

/*
 * Employee-facing CLI options.
 */
void Employee::displayMenu() const
{
    cout << "\n=== " << getRoleDisplay() << " Menu ===\n";
    cout << "1. View Full Inventory\n";
    cout << "2. Search Item\n";
    cout << "3. Record Sale / Make Transaction\n";
    cout << "0. Logout\n";
}

/*
 * Simple accessors.
 */
const string &Employee::getEmployeeId() const
{
    return employeeId;
}

string Employee::getRoleDisplay() const
{
    return "Employee";
}
