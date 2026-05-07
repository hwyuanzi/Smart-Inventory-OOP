#include "manager.h"

#include <iostream>
#include <string>
using namespace std;

/*
 * Parameterized constructor for creating a Manager object.
 * Initializes the manager account using the Employee base class
 * constructor and assigns the role as "manager".
 */
Manager::Manager(const string &username, const string &password, const string &managerId)
    : Employee(username, password, managerId), managerId(managerId)
{
    role = "manager";
}

/*
 * Getter Method
 */
const string &Manager::getManagerId() const
{
    return managerId;
}

/*
 * Adds a new item to the inventory system.
 */
void Manager::addItem(Inventory &inventory, const Item &item) const
{
    inventory.addItem(item);
}

/*
 * Deletes an item from the inventory using its ID.
 * Stores a success or failure message in msg.
 *
 * Returns true if the item was successfully removed;
 * otherwise returns false.
 */
bool Manager::deleteItem(Inventory &inventory, const string &itemId, string &msg) const
{
    const bool ok = inventory.removeItem(itemId);
    msg = ok ? "Item deleted successfully." : "Failed to delete item.";
    return ok;
}

/*
 * Retrieves all items currently marked
 * as low in stock.
 *
 * Returns a vector containing pointers
 * to low-stock items.
 */
vector<Item *> Manager::checkLowStockAlerts(Inventory &inventory) const
{
    return inventory.getLowStockItems();
}

/*
 * Updates an item's details including its
 * name, price, threshold, and category.
 * Stores a success or failure message in msg.
 *
 * Returns true if the update succeeds;
 * otherwise returns false.
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
 * Updates the stock quantity of a specific item.
 * Stores a success or failure message in msg.
 *
 * Returns true if the quantity update succeeds;
 * otherwise returns false.
 */
bool Manager::updateStockQuantity(Inventory &inventory, const string &id, int qty, string &msg) const
{
    const bool ok = inventory.updateStockQuantity(id, qty);
    msg = ok ? "Stock quantity updated." : "Unable to update stock quantity.";
    return ok;
}

/*
 * Returns all current restock requests
 * stored in the inventory system.
 */
vector<RestockRequest> &Manager::reviewRestockRequests(Inventory &inventory) const
{
    return inventory.getRestockRequests();
}

/*
 * Processes and fulfills a restock request
 * for a specific item.
 *
 * The method:
 * 1. Verifies the item exists.
 * 2. Searches for a matching restock request.
 * 3. Adds the requested quantity to inventory stock.
 * 4. Removes the completed restock request.
 *
 * Returns true if the request is fulfilled successfully;
 * otherwise returns false and stores an error message in msg.
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
 * Displays the manager menu options
 * available in the inventory system.
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
 * Returns the display name of the role.
 */
string Manager::getRoleDisplay() const
{
    return "Manager";
}
