#include "item.h"
#include <string>
#include <iostream>
using namespace std;

Item::Item(int id, string name, int qty, double price, int threshold)
{
    this->id = id;
    this->name = name;
    this->qty = qty;
    this->price = price;
    this->threshold = threshold;
}

int Item::getID() const
{
    return id;
}

string Item::getName() const
{
    return name;
}

int Item::getQuantity() const
{
    return qty;
}

double Item::getPrice() const
{
    return price;
}

int Item::getThreshold() const
{
    return threshold;
}

void Item::setName(string name)
{
    this->name = name;
}

void Item::setQuantity(int qty)
{
    this->qty = qty;
}

void Item::setPrice(double price)
{
    this->price = price;
}

void Item::display() const
{
    cout << "ID: " << id
         << " | Name: " << name
         << " | Quantity: " << qty
         << " | Price: " << price
         << " | Threshold: " << threshold << endl;
}