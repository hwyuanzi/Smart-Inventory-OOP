#include "manager.h"
#include "inventory.h"
#include "inputHelper.h"
#include <iostream>
using namespace std;

void Manager::menu(Inventory &inventory)
{
    int choice;

    do
    {
        cout << "\n---- Manager Menu ----\n";
        cout << "1. View Inventory" << endl;
        cout << "2. Search Item" << endl;
        cout << "3. Record Sale" << endl;
        cout << "4. Add Item" << endl;
        cout << "5. Delete Item" << endl;
        cout << "6. Check Low Stock" << endl;
        cout << "7. Update Item Quantity" << endl;
        cout << "8. View Restock Requests" << endl;
        cout << "9. Fulfill Restock Requests" << endl;
        cout << "\n0. Back to Main Menu" << endl;
        cout << "-1. Exit SmartInventory" << endl;

        choice = InputHelper::getInt("\nChoose option: ");

        if (choice == 1)
        {
            inventory.displayAll();
        }

        else if (choice == 2)
        {
            int id = InputHelper::getInt("Enter Item ID: ");
            Item *item = inventory.searchItem(id);

            if (item)
                item->display();
            else
                cout << "\nItem not found.\n";
        }

        else if (choice == 3)
        {
            int id = InputHelper::getInt("Enter Item ID: ");
            Item *item = inventory.searchItem(id);

            if (item)
            {
                item->display();
                int qty = InputHelper::getInt("Enter Qty Sold: ");
                inventory.recordSale(id, qty);
            }
            else
            {
                cout << "\nItem not found.\n";
            }
        }

        else if (choice == 4)
        {
            string name = InputHelper::getString("Enter Name: ");
            int qty = InputHelper::getInt("Enter Quantity: ");
            double price = InputHelper::getDouble("Enter Price: ");
            int threshold = InputHelper::getInt("Enter Threshold: ");

            inventory.addItem(name, qty, price, threshold);
            cout << "Item added successfully.";
        }

        else if (choice == 5)
        {
            int id = InputHelper::getInt("Enter Item ID to delete: ");
            inventory.removeItem(id);
        }

        else if (choice == 6)
        {
            inventory.checkLowStock();
        }

        else if (choice == 7)
        {
            int id = InputHelper::getInt("Enter Item ID: ");
            Item *item = inventory.searchItem(id);

            if (item)
            {
                int qty = InputHelper::getInt("Enter new qty: ");
                item->setQuantity(qty);
                cout << "\nQuantity updated.\n";
            }
            else
            {
                cout << "\nItem not found.\n";
            }
        }

        else if (choice == 8)
        {
            inventory.viewRestockReq();
        }

        else if (choice == 9)
        {
            int id = InputHelper::getInt("Enter Item ID to restock: ");
            inventory.fulfillRestockReq(id);
        }

    } while (choice != 0 && choice != -1);

    if (choice == -1)
    {
        cout << "\nThank you for using SmartInventory!";
        exit(0);
    }
}