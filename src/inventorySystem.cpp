#include "inventorySystem.h"
#include "manager.h"
#include "employee.h"
#include "inputHelper.h"
#include <iostream>
using namespace std;

void InventorySystem::run()
{
    int role;

    while (true)
    {
        cout << "\n---- SmartInventory System ----\n";
        cout << "1. Manager" << endl;
        cout << "2. Employee" << endl;
        cout << "0. Exit" << endl;

        role = InputHelper::getInt("Choose role: ");

        if (role == 1)
        {
            Manager manager;
            manager.menu(inventory);
        }
        else if (role == 2)
        {
            Employee employee;
            employee.menu(inventory);
        }
        else if (role == 0)
        {
            cout << "\nExiting system...\n";
            cout << "\nThank you for using with SmartInventory!";
            break;
        }
        else
        {
            cout << "\nInvalid choice.\n";
        }
    }
}