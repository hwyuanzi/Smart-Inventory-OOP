#include "item.h"
#include <string>
#include <iostream>
using namespace std;

Item::Item(int id, string name, int quantity, double price)
{
    this->id = id;
    this->name = name;
    this->quantity = quantity;
    this->price = price;
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
    return quantity;
}

double Item::getPrice() const
{
    return price;
}

void Item::setName(string name)
{
    this->name = name;
}

void Item::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void Item::setPrice(double price)
{
    this->price = price;
}

void Item::display() const
{
    cout << "ID: " << id << endl;
    cout << "Name:" << name << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price: " << price << endl;
}