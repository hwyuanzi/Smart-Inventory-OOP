#include "manager.h"
#include <string>
#include <iostream>
using namespace std;

Manager::Manager(string username, Inventory &inventory)
    : User(username), inventory(inventory) {}

void Manager::menu()
{
    int choice;
    do
    {
        cout << "\n--- Manager Menu ---\n";
        cout << "1. Add Item\n2. Remove Item\n3. Update Item\n4. View Inventory\n5.Quit";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addItem();
            break;
        case 2:
            removeItem();
            break;
        case 3:
            updateItem();
            break;
        case 4:
            inventory.display();
            break;
        }
    } while (choice != 5);
}

void Manager::addItem()
{
    int id, quantity;
    string name;
    double price;

    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price: ";
    cin >> price;

    inventory.addItem(Item(id, name, quantity, price));
}

void Manager::removeItem()
{
    int id;
    cout << "Enter ID to remove: ";
    cin >> id;
    inventory.removeItem(id);
}

void Manager::updateItem()
{
    int id, quantity;
    string name;
    double price;

    cout << "Enter ID to update: ";
    cin >> id;
    cout << "New Name: ";
    cin >> name;
    cout << "New Quantity: ";
    cin >> quantity;
    cout << "New Price: ";
    cin >> price;

    if (!inventory.updateItem(id, name, quantity, price))
    {
        cout << "Item not found." << endl;
    }
}