#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"
#include "restockReq.h"
using namespace std;

class Inventory
{
private:
    vector<Item> items;
    vector<RestockRequest> requests;
    static int nextID;

public:
    void addItem(string name, int qty, double price, int threshold);
    void removeItem(int id);
    void displayAll() const;
    void checkLowStock() const;
    bool recordSale(int id, int qty);
    bool updateItem(int id, string name, int qty, double price);

    Item *searchItem(int id);

    void generateRestockReq(const Item &item);
    void viewRestockReq() const;
    void fulfillRestockReq(int id);
};

#endif