#pragma once

#include "inventory.h"
#include "transaction.h"
#include "user.h"

#include <vector>

class Employee : public User
{
    /*
     * Available to Manager because Manager extends Employee.
     */
protected:
    string employeeId;

public:
    /*
     * Create an employee account.
     */
    Employee(const string &username, const string &password, const string &employeeId);

    /*
     * Employee menu actions.
     */
    void viewInventory(Inventory &inventory) const;
    vector<Item *> searchItem(Inventory &inventory, const string &query) const;
    bool makeTransaction(Inventory &inventory, vector<Transaction> &transactions, const string &id, int qty, string &msg) const;
    void displayMenu() const override;

    /*
     * Employee identity helpers.
     */
    const string &getEmployeeId() const;
    string getRoleDisplay() const override;
};
