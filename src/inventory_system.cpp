#include "inventory_system.h"

#include <iostream>
#include <limits>

InventorySystem::InventorySystem()
    : employee("employee"), manager("admin", "admin123") {}

void InventorySystem::seedDemoData()
{
    inventory.addItem(Item(1001, "Apple", 20, 0.99, 10));
    inventory.addItem(Item(1002, "Banana", 8, 0.49, 10));
    inventory.addItem(Item(1003, "Milk", 15, 2.79, 6));
    inventory.addItem(Item(1004, "Bread", 5, 3.50, 5));
}

int InventorySystem::readInt(const std::string &prompt, int minValue, int maxValue) const
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
        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double InventorySystem::readDouble(const std::string &prompt, double minValue) const
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
        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string InventorySystem::readLine(const std::string &prompt) const
{
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void InventorySystem::showLowStockAlertForItem(int id) const
{
    const Item *item = inventory.findItemById(id);
    if (item != nullptr && item->isLowStock())
    {
        std::cout << "Low-stock alert: " << item->getName()
                  << " now has quantity " << item->getQuantity()
                  << " (threshold: " << item->getStockThreshold() << ").\n";
    }
}

void InventorySystem::employeeSession()
{
    while (true)
    {
        employee.menu();
        const int choice = readInt("Select an option: ", 0, 3);

        if (choice == 0)
        {
            return;
        }

        if (choice == 1)
        {
            inventory.displayAll();
        }
        else if (choice == 2)
        {
            const std::string keyword = readLine("Enter name keyword: ");
            const std::vector<const Item *> matches = inventory.searchItemsByName(keyword);
            if (matches.empty())
            {
                std::cout << "No matching items found.\n";
            }
            else
            {
                for (const Item *item : matches)
                {
                    std::cout << "-------------------------\n";
                    item->display();
                }
                std::cout << "-------------------------\n";
            }
        }
        else if (choice == 3)
        {
            const int id = readInt("Enter item ID: ", 1, 1000000);
            const int qty = readInt("Enter quantity sold: ", 1, 1000000);
            if (inventory.recordSale(id, qty))
            {
                std::cout << "Transaction recorded.\n";
                showLowStockAlertForItem(id);
            }
            else
            {
                std::cout << "Transaction failed. Check item ID and available stock.\n";
            }
        }
    }
}

void InventorySystem::managerSession()
{
    const std::string password = readLine("Enter manager password: ");
    if (!manager.authenticate(password))
    {
        std::cout << "Authentication failed.\n";
        return;
    }

    std::cout << "Authentication successful.\n";

    while (true)
    {
        manager.menu();
        const int choice = readInt("Select an option: ", 0, 7);

        if (choice == 0)
        {
            return;
        }

        if (choice == 1)
        {
            const int id = readInt("Item ID: ", 1, 1000000);
            const std::string name = readLine("Name: ");
            const int qty = readInt("Quantity: ", 0, 1000000);
            const double price = readDouble("Price: ", 0.0);
            const int threshold = readInt("Low-stock threshold: ", 0, 1000000);

            if (inventory.addItem(Item(id, name, qty, price, threshold)))
            {
                std::cout << "Item added.\n";
            }
            else
            {
                std::cout << "Add failed: item ID already exists.\n";
            }
        }
        else if (choice == 2)
        {
            const int id = readInt("Item ID to delete: ", 1, 1000000);
            if (inventory.deleteItemById(id))
            {
                std::cout << "Item deleted.\n";
            }
            else
            {
                std::cout << "Delete failed: item not found.\n";
            }
        }
        else if (choice == 3 || choice == 6)
        {
            const std::vector<const Item *> lowStockItems = inventory.getLowStockItems();
            if (lowStockItems.empty())
            {
                std::cout << "No low-stock items.\n";
            }
            else
            {
                std::cout << "Low-stock / restock candidates:\n";
                for (const Item *item : lowStockItems)
                {
                    std::cout << "-------------------------\n";
                    item->display();
                }
                std::cout << "-------------------------\n";
            }
        }
        else if (choice == 4)
        {
            const int id = readInt("Item ID to update: ", 1, 1000000);
            const Item *existing = inventory.findItemById(id);
            if (existing == nullptr)
            {
                std::cout << "Update failed: item not found.\n";
                continue;
            }

            const std::string name = readLine("New name: ");
            const double price = readDouble("New price: ", 0.0);
            const int threshold = readInt("New low-stock threshold: ", 0, 1000000);
            if (inventory.updateItemDetails(id, name, price, threshold))
            {
                std::cout << "Item details updated.\n";
            }
        }
        else if (choice == 5)
        {
            const int id = readInt("Item ID to update stock: ", 1, 1000000);
            const int qty = readInt("New quantity: ", 0, 1000000);
            if (inventory.updateStockQuantity(id, qty))
            {
                std::cout << "Stock quantity updated.\n";
                showLowStockAlertForItem(id);
            }
            else
            {
                std::cout << "Update failed: item not found.\n";
            }
        }
        else if (choice == 7)
        {
            inventory.displayAll();
        }
    }
}

void InventorySystem::run()
{
    seedDemoData();

    while (true)
    {
        std::cout << "\n=== SmartInventory System ===\n";
        std::cout << "1. Employee Login\n";
        std::cout << "2. Manager Login\n";
        std::cout << "0. Exit\n";

        const int role = readInt("Select role: ", 0, 2);
        if (role == 0)
        {
            std::cout << "Goodbye.\n";
            return;
        }

        if (role == 1)
        {
            employeeSession();
        }
        else
        {
            managerSession();
        }
    }
}
