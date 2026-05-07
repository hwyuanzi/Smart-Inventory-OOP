#pragma once

#include "inventory.h"
#include "transaction.h"
#include "user.h"

#include <vector>

class Employee : public User
{
protected:
    std::string employeeId;

public:
    Employee(const std::string &username, const std::string &password, const std::string &employeeId);
    const std::string &getEmployeeId() const;
    void viewInventory(Inventory &inventory) const;
    std::vector<Item *> searchItem(Inventory &inventory, const std::string &query) const;
    bool makeTransaction(Inventory &inventory, std::vector<Transaction> &transactions, const std::string &id, int qty, std::string &msg) const;
    void displayMenu() const override;
    std::string getRoleDisplay() const override;
};
