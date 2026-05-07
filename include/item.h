#pragma once

#include <string>

class Item
{
private:
    std::string itemId;
    std::string name;
    int quantity;
    double price;
    int threshold;
    std::string category;

public:
    Item(const std::string &id, const std::string &name, int qty, double price, int thresh, const std::string &category);

    const std::string &getItemId() const;
    const std::string &getName() const;
    int getQuantity() const;
    double getPrice() const;
    int getThreshold() const;
    const std::string &getCategory() const;

    void setName(const std::string &name);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setThreshold(int threshold);
    void setCategory(const std::string &category);

    bool isLowStock() const;
    std::string toString() const;
};