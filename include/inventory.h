#pragma once

#include "item.h"

#include <string>
#include <vector>

class Inventory
{
private:
    std::vector<Item> items;

    static std::string toLower(const std::string &text);

public:
    bool addItem(const Item &item);
    bool deleteItemById(int id);
    Item *findItemById(int id);
    const Item *findItemById(int id) const;
    std::vector<const Item *> searchItemsByName(const std::string &namePart) const;
    bool recordSale(int id, int quantitySold);
    bool updateItemDetails(int id, const std::string &name, double price, int threshold);
    bool updateStockQuantity(int id, int quantity);
    std::vector<const Item *> getLowStockItems() const;
    bool isEmpty() const;
    void displayAll() const;
};
