#include "manager.h"

#include <iostream>
#include <string>
using namespace std;

/*
 * Managers share Employee behavior, then override the role used by login/menu code.
 */
Manager::Manager(const string &username, const string &password, const string &managerId)
    : Employee(username, password, managerId), managerId(managerId)
{
    role = "manager";
}

/*
 * Manager ID accessor.
 */
const string &Manager::getManagerId() const
{
    return managerId;
}

/*
 * Manager wrapper around adding inventory.
 */
void Manager::addItem(Inventory &inventory, const Item &item) const
{
    inventory.addItem(item);
}

/*
 * Delete by ID and return a message the CLI can print directly.
 */
bool Manager::deleteItem(Inventory &inventory, const string &itemId, string &msg) const
{
    const bool ok = inventory.removeItem(itemId);
    msg = ok ? "Item deleted successfully." : "Failed to delete item.";
    return ok;
}

/*
 * Pull the current low-stock list for manager review.
 */
vector<Item *> Manager::checkLowStockAlerts(Inventory &inventory) const
{
    return inventory.getLowStockItems();
}

/*
 * Update item metadata and keep the user-facing status message close by.
 */
bool Manager::updateItemDetails(
    Inventory &inventory,
    const string &id,
    const string &name,
    double price,
    int threshold,
    const string &category,
    string &msg) const
{
    const bool ok = inventory.updateItem(id, name, price, threshold, category);
    msg = ok ? "Item details updated successfully." : "Unable to update item details.";
    return ok;
}

/*
 * Direct stock adjustment for manager corrections or manual restocks.
 */
bool Manager::updateStockQuantity(Inventory &inventory, const string &id, int qty, string &msg) const
{
    const bool ok = inventory.updateStockQuantity(id, qty);
    msg = ok ? "Stock quantity updated." : "Unable to update stock quantity.";
    return ok;
}

/*
 * Return the live restock request list for review.
 */
vector<RestockRequest> &Manager::reviewRestockRequests(Inventory &inventory) const
{
    return inventory.getRestockRequests();
}

/*
 * Fulfill the matching request, add the requested stock, then remove the request.
 */
bool Manager::fulfillRestockRequest(Inventory &inventory, const string &itemId, string &msg) const
{
    Item *item = inventory.findItem(itemId);
    if (item == nullptr)
    {
        msg = "Item not found.";
        return false;
    }

    for (const RestockRequest &request : inventory.getRestockRequests())
    {
        if (request.getItemId() == itemId)
        {
            const int newQty = item->getQuantity() + request.getRequestedQuantity();
            const bool updated = inventory.updateStockQuantity(itemId, newQty);
            if (!updated)
            {
                msg = "Failed to update stock while fulfilling request.";
                return false;
            }

            inventory.clearRestockRequest(itemId);
            msg = "Restock fulfilled. New qty: " + to_string(newQty);
            return true;
        }
    }

    msg = "No restock request found for this item.";
    return false;
}

/*
 * Manager-facing CLI options.
 */
void Manager::displayMenu() const
{
    cout << "\n=== " << getRoleDisplay() << " Menu ===\n";
    cout << "1. View Full Inventory\n";
    cout << "2. Search Item\n";
    cout << "3. Record Sale / Make Transaction\n";
    cout << "4. Add Item\n";
    cout << "5. Delete Item\n";
    cout << "6. Check Low Stock Alerts\n";
    cout << "7. Update Item Details\n";
    cout << "8. Update Stock Quantity\n";
    cout << "9. Review Restock Requests\n";
    cout << "0. Logout\n";
}

/*
 * Label used in menu headers.
 */
string Manager::getRoleDisplay() const
{
    return "Manager";
}
