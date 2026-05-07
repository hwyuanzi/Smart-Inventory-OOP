#include "item.h"

#include <iostream>
#include <iomanip>

Item::Item(int id, const std::string &name, int quantity, double price, int stockThreshold)
    : id(id), name(name), quantity(quantity), price(price), stockThreshold(stockThreshold) {}

int Item::getID() const
{
    return id;
}

const std::string &Item::getName() const
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

int Item::getStockThreshold() const
{
    return stockThreshold;
}

void Item::setName(const std::string &name)
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

void Item::setStockThreshold(int stockThreshold)
{
    this->stockThreshold = stockThreshold;
}

bool Item::isLowStock() const
{
    return quantity <= stockThreshold;
}

void Item::display() const
{
    std::cout << "ID: " << id << '\n';
    std::cout << "Name: " << name << '\n';
    std::cout << "Quantity: " << quantity << '\n';
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << '\n';
    std::cout << "Threshold: " << stockThreshold << '\n';
}