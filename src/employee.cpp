#include "employee.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
std::string nowTimestamp()
{
    const std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);
    std::ostringstream stream;
    stream << std::put_time(&local, "%Y-%m-%d %H:%M:%S");
    return stream.str();
}
}

Employee::Employee(const std::string &username, const std::string &password, const std::string &employeeId)
    : User(username, password, "employee"), employeeId(employeeId) {}

const std::string &Employee::getEmployeeId() const
{
    return employeeId;
}

void Employee::viewInventory(Inventory &inventory) const
{
    std::vector<Item> &items = inventory.getAllItems();
    if (items.empty())
    {
        std::cout << "Inventory is empty.\n";
        return;
    }
    for (const Item &item : items)
    {
        std::cout << item.toString() << '\n';
    }
}

std::vector<Item *> Employee::searchItem(Inventory &inventory, const std::string &query) const
{
    return inventory.searchByName(query);
}

bool Employee::makeTransaction(Inventory &inventory, std::vector<Transaction> &transactions, const std::string &id, int qty, std::string &msg) const
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

    if (item->isLowStock())
    {
        const int requestQty = std::max(1, item->getThreshold() * 2 - item->getQuantity());
        inventory.addRestockRequest(RestockRequest(
            inventory.generateRestockId(),
            item->getItemId(),
            item->getName(),
            item->getQuantity(),
            requestQty,
            nowTimestamp()));
    }

    transactions.emplace_back(
        "T" + std::to_string(static_cast<int>(transactions.size()) + 1),
        id,
        item->getName(),
        qty,
        total,
        nowTimestamp());

    msg = "Transaction recorded successfully.";
    return true;
}

void Employee::displayMenu() const
{
    std::cout << "\n=== " << getRoleDisplay() << " Menu ===\n";
    std::cout << "1. View Full Inventory\n";
    std::cout << "2. Search Item\n";
    std::cout << "3. Record Sale / Make Transaction\n";
    std::cout << "0. Logout\n";
}

std::string Employee::getRoleDisplay() const
{
    return "Employee";
}
