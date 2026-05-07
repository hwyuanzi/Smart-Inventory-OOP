#include "employee.h"

#include <iostream>

Employee::Employee(const std::string &username) : User(username) {}

void Employee::menu() const
{
    std::cout << "\n=== Employee Menu ===\n";
    std::cout << "1. View Full Inventory\n";
    std::cout << "2. Search Item\n";
    std::cout << "3. Record Sale / Make Transaction\n";
    std::cout << "0. Logout\n";
}
