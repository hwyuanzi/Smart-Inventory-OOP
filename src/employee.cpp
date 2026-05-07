#include "employee.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * Helper function that generates the current
 * local date and time as a formatted timestamp.
 * Used for transaction and restock request records.
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
 * Parameterized constructor for creating an Employee object.
 * Initializes the employee account with a username,
 * password, and employee ID while assigning the role
 * as "employee" through the base User class.
 */
Employee::Employee(const string &username, const string &password, const string &employeeId)
    : User(username, password, "employee"), employeeId(employeeId) {}

/*
 * Displays all inventory items to the console.
 * If the inventory is empty, an appropriate
 * message is shown to the user.
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
 * Searches the inventory for items matching
 * the provided query string.
 *
 * Returns a vector containing pointers
 * to all matching items.
 */
vector<Item *> Employee::searchItem(Inventory &inventory, const string &query) const
{
    return inventory.searchByName(query);
}

/*
 * Processes a sales transaction for a specific item.
 *
 * The method:
 * 1. Verifies the item exists.
 * 2. Validates the requested quantity.
 * 3. Calculates the transaction total.
 * 4. Updates inventory stock quantity.
 * 5. Automatically creates a restock request
 *    if the item becomes low in stock.
 * 6. Records the completed transaction.
 *
 * Returns true if the transaction succeeds;
 * otherwise returns false and stores an
 * error message in the provided msg variable.
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
     * Automatically generate a restock request
     * if the updated quantity falls below
     * the item's threshold.
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
     * Record the successful transaction
     * in the transaction history.
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
 * Displays the employee menu options
 * available in the inventory system.
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
 * Getter Methods
 */
const string &Employee::getEmployeeId() const
{
    return employeeId;
}

string Employee::getRoleDisplay() const
{
    return "Employee";
}
