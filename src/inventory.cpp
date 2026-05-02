#include "inventory.h"
#include <iostream>
using namespace std;

void Inventory::addItem(const Item &item)
{
    items.push_back(item);
}

void Inventory::removeItem(int id)
{
    bool found = false;

    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getID() == id)
        {
            items.erase(items.begin() + i);
            cout << "Items removed successfully." << endl;
            found = true;
            break; // stop once we remove it
        }
    }
    if (!found)
    {
        cout << "Item not found." << endl;
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

void Inventory::display() const
{
    if (items.empty())
    {
        cout << "Inventory is empty." << endl;
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