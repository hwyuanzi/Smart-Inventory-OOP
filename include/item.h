#pragma once

#include <string>

class Item
{
private:
    int id;
    std::string name;
    int quantity;
    double price;
    int stockThreshold;

public:
    Item(int id, const std::string &name, int quantity, double price, int stockThreshold);

    int getID() const;
    const std::string &getName() const;
    int getQuantity() const;
    double getPrice() const;
    int getStockThreshold() const;

    void setName(const std::string &name);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setStockThreshold(int stockThreshold);

    bool isLowStock() const;
    void display() const;
};