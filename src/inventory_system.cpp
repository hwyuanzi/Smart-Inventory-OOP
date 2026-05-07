#include "inventory_system.h"

#include <cstdlib>
#include <iostream>
#include <limits>

InventorySystem::InventorySystem()
    : currentUser(nullptr), nextItemId(1001), nextEmployeeId(101), nextManagerId(101)
{
    users.push_back(new Employee("employee", "emp123", "E-100"));
    users.push_back(new Manager("manager", "admin123", "M-100"));
    initializeData();
}

InventorySystem::~InventorySystem()
{
    for (User *user : users)
    {
        delete user;
    }
}

int InventorySystem::readInt(const std::string &prompt, int minValue, int maxValue)
{
    int value = 0;
    while (true)
    {
        std::cout << prompt;
        if ((std::cin >> value) && value >= minValue && value <= maxValue)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        if (std::cin.eof())
        {
            std::cout << "\nInput closed.\n";
            std::exit(0);
        }
        std::cout << "Invalid integer input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double InventorySystem::readDouble(const std::string &prompt, double minValue)
{
    double value = 0.0;
    while (true)
    {
        std::cout << prompt;
        if ((std::cin >> value) && value >= minValue)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        if (std::cin.eof())
        {
            std::cout << "\nInput closed.\n";
            std::exit(0);
        }
        std::cout << "Invalid numeric input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string InventorySystem::readLine(const std::string &prompt)
{
    std::cout << prompt;
    std::string value;
    if (!std::getline(std::cin, value))
    {
        std::cout << "\nInput closed.\n";
        std::exit(0);
    }
    return value;
}

std::string InventorySystem::generateItemId()
{
    return "I" + std::to_string(nextItemId++);
}

std::string InventorySystem::generateEmployeeId()
{
    return "E-" + std::to_string(nextEmployeeId++);
}

std::string InventorySystem::generateManagerId()
{
    return "M-" + std::to_string(nextManagerId++);
}

bool InventorySystem::usernameExists(const std::string &username) const
{
    for (const User *user : users)
    {
        if (user->getUsername() == username)
        {
            return true;
        }
    }
    return false;
}

void InventorySystem::initializeData()
{
    inventory.addItem(Item(generateItemId(), "Apple", 20, 0.99, 10, "Produce"));
    inventory.addItem(Item(generateItemId(), "Banana", 8, 0.49, 10, "Produce"));
    inventory.addItem(Item(generateItemId(), "Milk", 15, 2.79, 6, "Dairy"));
    inventory.addItem(Item(generateItemId(), "Bread", 5, 3.50, 5, "Bakery"));
}

User *InventorySystem::login()
{
    std::cout << "\nLogin as:\n";
    std::cout << "1. Employee\n";
    std::cout << "2. Manager\n";
    const int roleChoice = readInt("Select role: ", 1, 2);
    const std::string selectedRole = roleChoice == 1 ? "employee" : "manager";

    const std::string username = readLine("Username: ");
    const std::string password = readLine("Password: ");
    for (User *user : users)
    {
        if (user->getRole() == selectedRole && user->getUsername() == username && user->authenticate(password))
        {
            return user;
        }
    }
    return nullptr;
}

void InventorySystem::signup()
{
    std::cout << "\nSign up as:\n";
    std::cout << "1. Employee\n";
    std::cout << "2. Manager\n";
    const int roleChoice = readInt("Select role: ", 1, 2);

    const std::string username = readLine("Choose username: ");
    if (username.empty())
    {
        std::cout << "Username cannot be empty.\n";
        return;
    }
    if (usernameExists(username))
    {
        std::cout << "Username already exists.\n";
        return;
    }

    const std::string password = readLine("Choose password: ");
    if (password.empty())
    {
        std::cout << "Password cannot be empty.\n";
        return;
    }

    if (roleChoice == 1)
    {
        const std::string employeeId = generateEmployeeId();
        users.push_back(new Employee(username, password, employeeId));
        std::cout << "Employee account created. Employee ID: " << employeeId << '\n';
    }
    else
    {
        const std::string managerId = generateManagerId();
        users.push_back(new Manager(username, password, managerId));
        std::cout << "Manager account created. Manager ID: " << managerId << '\n';
    }
}

void InventorySystem::handleEmployeeMenu(Employee *employee)
{
    while (true)
    {
        employee->displayMenu();
        const int choice = readInt("Select option: ", 0, 3);
        if (choice == 0)
        {
            break;
        }

        if (choice == 1)
        {
            employee->viewInventory(inventory);
        }
        else if (choice == 2)
        {
            const std::string query = readLine("Search keyword: ");
            std::vector<Item *> matches = employee->searchItem(inventory, query);
            if (matches.empty())
            {
                std::cout << "No item found.\n";
            }
            for (const Item *item : matches)
            {
                std::cout << item->toString() << '\n';
            }
        }
        else if (choice == 3)
        {
            const std::string itemId = readLine("Item ID: ");
            const int qty = readInt("Quantity sold: ", 1, 1000000);
            std::string msg;
            employee->makeTransaction(inventory, transactions, itemId, qty, msg);
            std::cout << msg << '\n';
        }
    }
}

void InventorySystem::handleManagerMenu(Manager *manager)
{
    while (true)
    {
        manager->displayMenu();
        const int choice = readInt("Select option: ", 0, 9);
        if (choice == 0)
        {
            break;
        }

        if (choice == 1)
        {
            manager->viewInventory(inventory);
        }
        else if (choice == 2)
        {
            const std::string query = readLine("Search keyword: ");
            std::vector<Item *> matches = manager->searchItem(inventory, query);
            if (matches.empty())
            {
                std::cout << "No item found.\n";
            }
            for (const Item *item : matches)
            {
                std::cout << item->toString() << '\n';
            }
        }
        else if (choice == 3)
        {
            const std::string itemId = readLine("Item ID: ");
            const int qty = readInt("Quantity sold: ", 1, 1000000);
            std::string msg;
            manager->makeTransaction(inventory, transactions, itemId, qty, msg);
            std::cout << msg << '\n';
        }
        else if (choice == 4)
        {
            const std::string name = readLine("Name: ");
            const std::string category = readLine("Category: ");
            const int qty = readInt("Quantity: ", 0, 1000000);
            const double price = readDouble("Price: ", 0.0);
            const int threshold = readInt("Threshold: ", 0, 1000000);
            manager->addItem(inventory, Item(generateItemId(), name, qty, price, threshold, category));
            std::cout << "Item added.\n";
        }
        else if (choice == 5)
        {
            const std::string id = readLine("Item ID: ");
            std::string msg;
            manager->deleteItem(inventory, id, msg);
            std::cout << msg << '\n';
        }
        else if (choice == 6)
        {
            std::vector<Item *> lowItems = manager->checkLowStockAlerts(inventory);
            if (lowItems.empty())
            {
                std::cout << "No low-stock items.\n";
            }
            for (const Item *item : lowItems)
            {
                std::cout << item->toString() << '\n';
            }
        }
        else if (choice == 7)
        {
            const std::string id = readLine("Item ID: ");
            const std::string name = readLine("New name: ");
            const std::string category = readLine("New category: ");
            const double price = readDouble("New price: ", 0.0);
            const int threshold = readInt("New threshold: ", 0, 1000000);
            std::string msg;
            manager->updateItemDetails(inventory, id, name, price, threshold, category, msg);
            std::cout << msg << '\n';
        }
        else if (choice == 8)
        {
            const std::string id = readLine("Item ID: ");
            const int qty = readInt("New quantity: ", 0, 1000000);
            std::string msg;
            manager->updateStockQuantity(inventory, id, qty, msg);
            std::cout << msg << '\n';
        }
        else if (choice == 9)
        {
            std::vector<RestockRequest> &requests = manager->reviewRestockRequests(inventory);
            if (requests.empty())
            {
                std::cout << "No restock requests.\n";
            }
            for (const RestockRequest &request : requests)
            {
                std::cout << "Request " << request.getRequestId()
                          << " | item " << request.getItemId()
                          << " | req qty " << request.getRequestedQuantity() << '\n';
            }
            const int doFulfill = readInt("Fulfill one request? (1/0): ", 0, 1);
            if (doFulfill == 1)
            {
                const std::string id = readLine("Item ID to fulfill: ");
                std::string msg;
                manager->fulfillRestockRequest(inventory, id, msg);
                std::cout << msg << '\n';
            }
        }
    }
}

void InventorySystem::run()
{
    while (true)
    {
        std::cout << "\n=== SmartInventory ===\n";
        std::cout << "1. Login\n";
        std::cout << "2. Sign Up\n";
        std::cout << "0. Exit\n";
        const int choice = readInt("Select: ", 0, 2);
        if (choice == 0)
        {
            std::cout << "Goodbye.\n";
            return;
        }

        if (choice == 2)
        {
            signup();
            continue;
        }

        currentUser = login();
        if (currentUser == nullptr)
        {
            std::cout << "Authentication failed.\n";
            continue;
        }

        if (currentUser->getRole() == "manager")
        {
            handleManagerMenu(dynamic_cast<Manager *>(currentUser));
        }
        else
        {
            handleEmployeeMenu(dynamic_cast<Employee *>(currentUser));
        }
    }
}
