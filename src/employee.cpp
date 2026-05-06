#include "employee.h"
#include "inventory.h"
#include "inputHelper.h"
#include <iostream>
using namespace std;

void Employee::menu(Inventory &inventory)
{
    int choice;

    do
    {
        cout << "\n---- Employee Menu ----\n";
        cout << "1. View Inventory" << endl;
        cout << "2. Search Item" << endl;
        cout << "3. Record Sale" << endl;

        cout << "\n0. Back to Main Menu" << endl;
        cout << "-1. Exit Program" << endl;

        choice = InputHelper::getInt("\nChoose Option: ");

        if (choice == 1)
        {
            inventory.displayAll();
        }
        else if (choice == 2)
        {
            int id = InputHelper::getInt("Enter item ID: ");
            Item *item = inventory.searchItem(id);

            if (item)
                item->display();
            else
                cout << "\nItem not found.\n";
        }
        else if (choice == 3)
        {
            int id = InputHelper::getInt("Enter item ID: ");
            Item *item = inventory.searchItem(id);

            if (item)
            {
                item->display();
                int qty = InputHelper::getInt("Enter Quantity Sold: ");
                inventory.recordSale(id, qty);
            }
            else
            {
                cout << "\nItem not found.\n";
            }
        }
    } while (choice != 0 && choice != -1);

    if (choice == -1)
    {
        cout << "\nThank you for using SmartInventory!";
        exit(0);
    }
}