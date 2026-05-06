#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item
{
    // private attributes
private:
    int id;
    string name;
    int qty;
    double price;
    int threshold;

public:
    Item(int id, string name, int qty, double price, int threshold);

    int getID() const;
    string getName() const;
    int getQuantity() const;
    double getPrice() const;
    int getThreshold() const;

    void setName(string name);
    void setQuantity(int qty);
    void setPrice(double price);

    // dispay item details
    void display() const;
};

#endif