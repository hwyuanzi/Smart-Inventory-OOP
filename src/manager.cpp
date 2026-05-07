#include "manager.h"

#include <iostream>

Manager::Manager(const std::string &username, const std::string &password)
    : User(username), password(password) {}

bool Manager::authenticate(const std::string &inputPassword) const
{
    return inputPassword == password;
}

void Manager::menu() const
{
    std::cout << "\n=== Manager Menu ===\n";
    std::cout << "1. Add Item\n";
    std::cout << "2. Delete Item\n";
    std::cout << "3. Check Low Stock Alerts\n";
    std::cout << "4. Update Item Details\n";
    std::cout << "5. Update Stock Quantity\n";
    std::cout << "6. Review Restock Requests\n";
    std::cout << "7. View Full Inventory\n";
    std::cout << "0. Logout\n";
}
