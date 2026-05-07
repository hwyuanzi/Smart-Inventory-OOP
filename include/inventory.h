#pragma once

#include "item.h"
#include "restock_request.h"

#include <string>
#include <vector>
using namespace std;

class Inventory
{
    /*
     * Inventory and pending restock state for the current run.
     */
private:
    vector<Item> items;
    vector<RestockRequest> restockRequests;
    int nextRestockId;
    static string toLower(const string &text);

public:
    Inventory();

    /*
     * Core inventory operations used by the CLI roles.
     */
    void addItem(const Item &item);
    bool removeItem(const string &itemId);
    Item *findItem(const string &itemId);
    vector<Item *> searchByName(const string &query);
    vector<Item> &getAllItems();
    bool updateItem(const string &id, const string &name, double price, int threshold, const string &category);
    bool updateStockQuantity(const string &id, int qty);
    vector<Item *> getLowStockItems();
    void addRestockRequest(const RestockRequest &request);
    vector<RestockRequest> &getRestockRequests();
    bool clearRestockRequest(const string &itemId);
    string generateRestockId();
};
