#include "manager.h"

#include <iostream>

Manager::Manager(const std::string &username, const std::string &password, const std::string &managerId)
    : Employee(username, password, managerId), managerId(managerId)
{
    role = "manager";
}

const std::string &Manager::getManagerId() const
{
    return managerId;
}

void Manager::addItem(Inventory &inventory, const Item &item) const
{
    inventory.addItem(item);
}

bool Manager::deleteItem(Inventory &inventory, const std::string &itemId, std::string &msg) const
{
    const bool ok = inventory.removeItem(itemId);
    msg = ok ? "Item deleted successfully." : "Failed to delete item.";
    return ok;
}

std::vector<Item *> Manager::checkLowStockAlerts(Inventory &inventory) const
{
    return inventory.getLowStockItems();
}

bool Manager::updateItemDetails(
    Inventory &inventory,
    const std::string &id,
    const std::string &name,
    double price,
    int threshold,
    const std::string &category,
    std::string &msg) const
{
    const bool ok = inventory.updateItem(id, name, price, threshold, category);
    msg = ok ? "Item details updated successfully." : "Unable to update item details.";
    return ok;
}

bool Manager::updateStockQuantity(Inventory &inventory, const std::string &id, int qty, std::string &msg) const
{
    const bool ok = inventory.updateStockQuantity(id, qty);
    msg = ok ? "Stock quantity updated." : "Unable to update stock quantity.";
    return ok;
}

std::vector<RestockRequest> &Manager::reviewRestockRequests(Inventory &inventory) const
{
    return inventory.getRestockRequests();
}

bool Manager::fulfillRestockRequest(Inventory &inventory, const std::string &itemId, std::string &msg) const
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
            msg = "Restock fulfilled. New qty: " + std::to_string(newQty);
            return true;
        }
    }

    msg = "No restock request found for this item.";
    return false;
}

void Manager::displayMenu() const
{
    std::cout << "\n=== " << getRoleDisplay() << " Menu ===\n";
    std::cout << "1. View Full Inventory\n";
    std::cout << "2. Search Item\n";
    std::cout << "3. Record Sale / Make Transaction\n";
    std::cout << "4. Add Item\n";
    std::cout << "5. Delete Item\n";
    std::cout << "6. Check Low Stock Alerts\n";
    std::cout << "7. Update Item Details\n";
    std::cout << "8. Update Stock Quantity\n";
    std::cout << "9. Review Restock Requests\n";
    std::cout << "0. Logout\n";
}

std::string Manager::getRoleDisplay() const
{
    return "Manager";
}
