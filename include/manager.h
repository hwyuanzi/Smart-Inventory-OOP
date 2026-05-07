#pragma once

#include "inventory.h"
#include "user.h"

#include <string>
#include <vector>

class Manager : public User
{
private:
    std::string managerId;

public:
    Manager(const std::string &username, const std::string &password, const std::string &managerId);
    const std::string &getManagerId() const;
    void addItem(Inventory &inventory, const Item &item) const;
    bool deleteItem(Inventory &inventory, const std::string &itemId, std::string &msg) const;
    std::vector<Item *> checkLowStockAlerts(Inventory &inventory) const;
    bool updateItemDetails(Inventory &inventory, const std::string &id, const std::string &name, double price, int threshold, const std::string &category, std::string &msg) const;
    bool updateStockQuantity(Inventory &inventory, const std::string &id, int qty, std::string &msg) const;
    std::vector<RestockRequest> &reviewRestockRequests(Inventory &inventory) const;
    bool fulfillRestockRequest(Inventory &inventory, const std::string &itemId, std::string &msg) const;
    void displayMenu() const override;
    std::string getRoleDisplay() const override;
};
