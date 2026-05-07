#pragma once

#include <string>
using namespace std;

class Item
{
    /*
     * Private Attributes
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
     * Public Constructor
     */
    Item(const string &id, const string &name, int qty, double price, int thresh, const string &category);

    /*
     * Getter Methods
     */
    const string &getItemId() const;
    const string &getName() const;
    int getQuantity() const;
    double getPrice() const;
    int getThreshold() const;
    const string &getCategory() const;

    /*
     * Setter Methods
     */
    void setName(const string &name);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setThreshold(int threshold);
    void setCategory(const string &category);

    bool isLowStock() const;
    string toString() const;
};