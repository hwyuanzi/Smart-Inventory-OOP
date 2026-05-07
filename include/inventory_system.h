#pragma once

#include "employee.h"
#include "inventory.h"
#include "manager.h"
#include "transaction.h"

#include <string>
#include <vector>

class InventorySystem
{
private:
    Inventory inventory;
    std::vector<User *> users;
    std::vector<Transaction> transactions;
    User *currentUser;
    int nextItemId;

    User *login();
    void handleEmployeeMenu(Employee *employee);
    void handleManagerMenu(Manager *manager);
    std::string generateItemId();
    void initializeData();
    int readInt(const std::string &prompt, int minValue, int maxValue);
    double readDouble(const std::string &prompt, double minValue);
    std::string readLine(const std::string &prompt);

public:
    InventorySystem();
    ~InventorySystem();
    void run();
};
