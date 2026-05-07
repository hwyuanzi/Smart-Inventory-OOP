#include "inventory_system.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

InventorySystem::InventorySystem()
    : currentUser(nullptr), nextItemID(1001), nextEmployeeId(101), nextManagerId(101)
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

int InventorySystem::readInt(const string &prompt, int minValue, int maxValue)
{
    int value = 0;
    while (true)
    {
        cout << prompt;
        if ((cin >> value) && value >= minValue && value <= maxValue)
        {
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof())
        {
            cout << "\nInput closed.\n";
            exit(0);
        }
        cout << "Invalid integer input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double InventorySystem::readDouble(const string &prompt, double minValue)
{
    double value = 0.0;
    while (true)
    {
        cout << prompt;
        if ((cin >> value) && value >= minValue)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof())
        {
            cout << "\nInput closed.\n";
            exit(0);
        }
        cout << "Invalid numeric input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string InventorySystem::readLine(const string &prompt)
{
    cout << prompt;
    string value;
    if (!getline(cin, value))
    {
        cout << "\nInput closed.\n";
        exit(0);
    }
    return value;
}

string InventorySystem::generateItemId()
{
    return "I" + to_string(nextItemID++);
}

string InventorySystem::generateEmployeeId()
{
    return "E-" + to_string(nextEmployeeId++);
}

string InventorySystem::generateManagerId()
{
    return "M-" + to_string(nextManagerId++);
}

bool InventorySystem::usernameExists(const string &username) const
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
    cout << "\nLogin as:\n";
    cout << "1. Employee\n";
    cout << "2. Manager\n";
    const int roleChoice = readInt("Select role: ", 1, 2);
    const string selectedRole = roleChoice == 1 ? "employee" : "manager";

    const string username = readLine("Username: ");
    const string password = readLine("Password: ");
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
    cout << "\nSign up as:\n";
    cout << "1. Employee\n";
    cout << "2. Manager\n";
    const int roleChoice = readInt("Select role: ", 1, 2);

    const string username = readLine("Choose username: ");
    if (username.empty())
    {
        cout << "Username cannot be empty.\n";
        return;
    }
    if (usernameExists(username))
    {
        cout << "Username already exists.\n";
        return;
    }

    const string password = readLine("Choose password: ");
    if (password.empty())
    {
        cout << "Password cannot be empty.\n";
        return;
    }

    if (roleChoice == 1)
    {
        const string employeeId = generateEmployeeId();
        users.push_back(new Employee(username, password, employeeId));
        cout << "Employee account created. Employee ID: " << employeeId << '\n';
    }
    else
    {
        const string managerId = generateManagerId();
        users.push_back(new Manager(username, password, managerId));
        cout << "Manager account created. Manager ID: " << managerId << '\n';
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
            const string query = readLine("Search keyword: ");
            vector<Item *> matches = employee->searchItem(inventory, query);
            if (matches.empty())
            {
                cout << "No item found.\n";
            }
            for (const Item *item : matches)
            {
                cout << item->toString() << '\n';
            }
        }
        else if (choice == 3)
        {
            const string itemId = readLine("Item ID: ");
            const int qty = readInt("Quantity sold: ", 1, 1000000);
            string msg;
            employee->makeTransaction(inventory, transactions, itemId, qty, msg);
            cout << msg << '\n';
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
            const string query = readLine("Search keyword: ");
            vector<Item *> matches = manager->searchItem(inventory, query);
            if (matches.empty())
            {
                cout << "No item found.\n";
            }
            for (const Item *item : matches)
            {
                cout << item->toString() << '\n';
            }
        }
        else if (choice == 3)
        {
            const string itemId = readLine("Item ID: ");
            const int qty = readInt("Quantity sold: ", 1, 1000000);
            string msg;
            manager->makeTransaction(inventory, transactions, itemId, qty, msg);
            cout << msg << '\n';
        }
        else if (choice == 4)
        {
            const string name = readLine("Name: ");
            const string category = readLine("Category: ");
            const int qty = readInt("Quantity: ", 0, 1000000);
            const double price = readDouble("Price: ", 0.0);
            const int threshold = readInt("Threshold: ", 0, 1000000);
            manager->addItem(inventory, Item(generateItemId(), name, qty, price, threshold, category));
            cout << "Item added.\n";
        }
        else if (choice == 5)
        {
            const string id = readLine("Item ID: ");
            string msg;
            manager->deleteItem(inventory, id, msg);
            cout << msg << '\n';
        }
        else if (choice == 6)
        {
            vector<Item *> lowItems = manager->checkLowStockAlerts(inventory);
            if (lowItems.empty())
            {
                cout << "No low-stock items.\n";
            }
            for (const Item *item : lowItems)
            {
                cout << item->toString() << '\n';
            }
        }
        else if (choice == 7)
        {
            const string id = readLine("Item ID: ");
            const string name = readLine("New name: ");
            const string category = readLine("New category: ");
            const double price = readDouble("New price: ", 0.0);
            const int threshold = readInt("New threshold: ", 0, 1000000);
            string msg;
            manager->updateItemDetails(inventory, id, name, price, threshold, category, msg);
            cout << msg << '\n';
        }
        else if (choice == 8)
        {
            const string id = readLine("Item ID: ");
            const int qty = readInt("New quantity: ", 0, 1000000);
            string msg;
            manager->updateStockQuantity(inventory, id, qty, msg);
            cout << msg << '\n';
        }
        else if (choice == 9)
        {
            vector<RestockRequest> &requests = manager->reviewRestockRequests(inventory);
            if (requests.empty())
            {
                cout << "No restock requests.\n";
            }
            for (const RestockRequest &request : requests)
            {
                cout << "Request " << request.getRequestId()
                     << " | item " << request.getItemId()
                     << " | req qty " << request.getRequestedQuantity() << '\n';
            }
            const int doFulfill = readInt("Fulfill one request? (1/0): ", 0, 1);
            if (doFulfill == 1)
            {
                const string id = readLine("Item ID to fulfill: ");
                string msg;
                manager->fulfillRestockRequest(inventory, id, msg);
                cout << msg << '\n';
            }
        }
    }
}

void InventorySystem::run()
{
    while (true)
    {
        cout << "\n=== SmartInventory ===\n";
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "0. Exit\n";
        const int choice = readInt("Select: ", 0, 2);
        if (choice == 0)
        {
            cout << "Thank you for using SmartInventory. Program exiting...\n";
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
            cout << "Authentication failed.\n";
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
