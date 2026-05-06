#include "inventory.h"
#include <iostream>
using namespace std;

int Inventory::nextID = 1;

void Inventory::addItem(string name, int qty, double price, int threshold)
{
    Item newItem(nextID++, name, qty, price, threshold);
    items.push_back(newItem);

    cout << "\nItem (ID: " << newItem.getID() << ")" << endl;
}

void Inventory::removeItem(int id)
{
    bool found = false;

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getID() == id)
        {
            items.erase(items.begin() + i);
            cout << "\nItem removed successfully." << endl;
            found = true;
            break; // stop once we remove it
        }
    }

    if (!found)
    {
        cout << "\nItem not found.\n"
             << endl;
    }
}

Item *Inventory::searchItem(int id)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getID() == id)
        {
            return &items[i];
        }
    }
    return nullptr;
}

void Inventory::displayAll() const
{
    if (items.empty())
    {
        cout << "\nInventory is empty." << endl;
        return;
    }

    cout << "\n--- Inventory List ---\n";

    for (int i = 0; i < items.size(); i++)
    {
        items[i].display();
    }
}

bool Inventory::updateItem(int id, string name, int quantity, double price)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getID() == id)
        {
            items[i].setName(name);
            items[i].setQuantity(quantity);
            items[i].setPrice(price);

            cout << "Item updated successfully." << endl;
            return true;
        }
    }
    return false;
}

void Inventory::checkLowStock() const
{
    bool found = false;

    for (const auto &item : items)
    {
        if (item.getQuantity() < item.getThreshold())
        {
            if (!found)
            {
                cout << "\n--- Low Stock Alerts ---\n";
            }

            found = true;
            item.display();
        }
    }

    if (!found)
    {
        cout << "\nNo low stock alert at this time.\n";
    }
}

bool Inventory::recordSale(int id, int qty)
{
    Item *item = searchItem(id);

    if (!item)
    {
        cout << "\nItem not found.\n";
        return false;
    }

    if (qty <= 0)
    {
        cout << "\nInvalid quantity.\n";
        return false;
    }

    if (qty > item->getQuantity())
    {
        cout << "\nNot enough stock.\n";
        return false;
    }

    item->setQuantity(item->getQuantity() - qty);
    cout << "\nSale recorded successfully.\n";

    if (item->getQuantity() < item->getThreshold())
    {
        cout << "\n⚠ Low stock alert triggered!\n";
        generateRestockReq(*item);
    }

    return true;
}

void Inventory::generateRestockReq(const Item &item)
{
    int needed = item.getThreshold();
    requests.push_back(RestockRequest(item.getID(), needed));

    cout << "\nRestock request created for Item ID: " << item.getID() << endl;
}

void Inventory::viewRestockReq() const
{
    if (requests.empty())
    {
        cout << "\nNo restock requests.\n";
        return;
    }
    cout << "\n--- Restock Requests ---\n";
    for (const auto &req : requests)
    {
        cout << "\nItem ID: " << req.getItemID() << " | Suggested Quantity: " << req.getSuggestedQty() << endl;
    }
}

void Inventory::fulfillRestockReq(int itemID)
{
    for (auto it = requests.begin(); it != requests.end(); it++)
    {
        if (it->getItemID() == itemID)
        {
            Item *item = searchItem(itemID);
            if (item)
            {
                item->setQuantity(item->getQuantity() + it->getSuggestedQty());
                cout << "\nRestock completed for Item ID: " << itemID << endl;
                requests.erase(it);
                return;
            }
        }
    }

    cout << "\nRequest not found.\n";
}
