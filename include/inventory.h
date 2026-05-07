#pragma once

#include "item.h"
#include "restock_request.h"

#include <string>
#include <vector>

class Inventory
{
private:
    std::vector<Item> items;
    std::vector<RestockRequest> restockRequests;
    int nextRestockId;

    static std::string toLower(const std::string &text);

public:
    Inventory();
    void addItem(const Item &item);
    bool removeItem(const std::string &itemId);
    Item *findItem(const std::string &itemId);
    std::vector<Item *> searchByName(const std::string &query);
    std::vector<Item> &getAllItems();
    bool updateItem(const std::string &id, const std::string &name, double price, int threshold, const std::string &category);
    bool updateStockQuantity(const std::string &id, int qty);
    std::vector<Item *> getLowStockItems();
    void addRestockRequest(const RestockRequest &request);
    std::vector<RestockRequest> &getRestockRequests();
    bool clearRestockRequest(const std::string &itemId);
    std::string generateRestockId();
};
