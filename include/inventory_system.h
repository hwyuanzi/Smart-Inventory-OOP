#pragma once

#include "employee.h"
#include "inventory.h"
#include "manager.h"
#include "transaction.h"

#include <string>
#include <vector>
using namespace std;

class InventorySystem
{
private:
    Inventory inventory;
    vector<User *> users;
    vector<Transaction> transactions;
    User *currentUser;
    int nextItemID;

    User *login();
    void handleEmployeeMenu(Employee *employee);
    void handleManagerMenu(Manager *manager);

    string generateItemId();

    void initializeData();

    int readInt(const string &prompt, int minValue, int maxValue);
    double readDouble(const string &prompt, double minValue);
    string readLine(const string &prompt);

public:
    InventorySystem();
    ~InventorySystem();
    void run();
};
