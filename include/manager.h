#pragma once

#include "employee.h"

#include <string>
#include <vector>
using namespace std;

class Manager : public Employee
{
    /*
     * Private attribute
     */
private:
    string managerId;

    /*
     * Public Constructor
     */
public:
    Manager(const string &username, const string &password, const string &managerId);

    /*
     * Manager Menu Operation Methods
     */
    const string &getManagerId() const;
    void addItem(Inventory &inventory, const Item &item) const;
    bool deleteItem(Inventory &inventory, const string &itemId, string &msg) const;
    vector<Item *> checkLowStockAlerts(Inventory &inventory) const;
    bool updateItemDetails(Inventory &inventory, const string &id, const string &name, double price, int threshold, const string &category, string &msg) const;
    bool updateStockQuantity(Inventory &inventory, const string &id, int qty, string &msg) const;
    vector<RestockRequest> &reviewRestockRequests(Inventory &inventory) const;
    bool fulfillRestockRequest(Inventory &inventory, const string &itemId, string &msg) const;
    void displayMenu() const override;
    string getRoleDisplay() const override;
};
