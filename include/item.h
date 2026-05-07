#pragma once

#include <string>
using namespace std;

class Item
{
    /*
     * Item state stored in memory.
     */
private:
    string itemId;
    string name;
    int quantity;
    double price;
    int threshold;
    string category;

public:
    /*
     * Build an item from generated/user-provided fields.
     */
    Item(const string &id, const string &name, int qty, double price, int thresh, const string &category);

    /*
     * Read access.
     */
    const string &getItemId() const;
    const string &getName() const;
    int getQuantity() const;
    double getPrice() const;
    int getThreshold() const;
    const string &getCategory() const;

    /*
     * Manager update hooks.
     */
    void setName(const string &name);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setThreshold(int threshold);
    void setCategory(const string &category);

    bool isLowStock() const;
    string toString() const;
};