#include "inventory_system.h"

#include <iostream>
#include <limits>

InventorySystem::InventorySystem() : currentUser(nullptr), nextItemId(1001)
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
        std::cout << "Invalid numeric input.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string InventorySystem::readLine(const std::string &prompt)
{
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

std::string InventorySystem::generateItemId()
{
    return "I" + std::to_string(nextItemId++);
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
    const std::string username = readLine("Username: ");
    const std::string password = readLine("Password: ");
    for (User *user : users)
    {
        if (user->getUsername() == username && user->authenticate(password))
        {
            return user;
        }
    }
    return nullptr;
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
        const int choice = readInt("Select option: ", 0, 7);
        if (choice == 0)
        {
            break;
        }

        if (choice == 1)
        {
            const std::string name = readLine("Name: ");
            const std::string category = readLine("Category: ");
            const int qty = readInt("Quantity: ", 0, 1000000);
            const double price = readDouble("Price: ", 0.0);
            const int threshold = readInt("Threshold: ", 0, 1000000);
            manager->addItem(inventory, Item(generateItemId(), name, qty, price, threshold, category));
            std::cout << "Item added.\n";
        }
        else if (choice == 2)
        {
            const std::string id = readLine("Item ID: ");
            std::string msg;
            manager->deleteItem(inventory, id, msg);
            std::cout << msg << '\n';
        }
        else if (choice == 3)
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
        else if (choice == 4)
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
        else if (choice == 5)
        {
            const std::string id = readLine("Item ID: ");
            const int qty = readInt("New quantity: ", 0, 1000000);
            std::string msg;
            manager->updateStockQuantity(inventory, id, qty, msg);
            std::cout << msg << '\n';
        }
        else if (choice == 6)
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
        else if (choice == 7)
        {
            std::vector<Item> &items = inventory.getAllItems();
            if (items.empty())
            {
                std::cout << "Inventory is empty.\n";
            }
            for (const Item &item : items)
            {
                std::cout << item.toString() << '\n';
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
        std::cout << "0. Exit\n";
        const int choice = readInt("Select: ", 0, 1);
        if (choice == 0)
        {
            std::cout << "Goodbye.\n";
            return;
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
