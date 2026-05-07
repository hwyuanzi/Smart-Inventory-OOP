#pragma once

#include "employee.h"
#include "inventory.h"
#include "manager.h"

#include <string>

class InventorySystem
{
private:
    Inventory inventory;
    Employee employee;
    Manager manager;

    int readInt(const std::string &prompt, int minValue, int maxValue) const;
    double readDouble(const std::string &prompt, double minValue) const;
    std::string readLine(const std::string &prompt) const;

    void showLowStockAlertForItem(int id) const;
    void employeeSession();
    void managerSession();

public:
    InventorySystem();
    void seedDemoData();
    void run();
};
