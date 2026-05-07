#pragma once

#include "inventory.h"
#include "transaction.h"
#include "user.h"

#include <vector>

class Employee : public User
{
    /*
     * Protected Attribute
     */
protected:
    string employeeId;

public:
    /*
     * Public Constructor
     */
    Employee(const string &username, const string &password, const string &employeeId);

    /*
     * Employee Menu Operation Methods
     */
    void viewInventory(Inventory &inventory) const;
    vector<Item *> searchItem(Inventory &inventory, const string &query) const;
    bool makeTransaction(Inventory &inventory, vector<Transaction> &transactions, const string &id, int qty, string &msg) const;
    void displayMenu() const override;

    /*
     * Getter Methods
     */
    const string &getEmployeeId() const;
    string getRoleDisplay() const override;
};
