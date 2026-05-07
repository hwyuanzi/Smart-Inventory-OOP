#include "item.h"

#include <iomanip>
#include <sstream>

Item::Item(const std::string &id, const std::string &name, int qty, double price, int thresh, const std::string &category)
    : itemId(id), name(name), quantity(qty), price(price), threshold(thresh), category(category) {}

const std::string &Item::getItemId() const
{
    return itemId;
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

int Item::getThreshold() const
{
    return threshold;
}

const std::string &Item::getCategory() const
{
    return category;
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

void Item::setThreshold(int threshold)
{
    this->threshold = threshold;
}

void Item::setCategory(const std::string &category)
{
    this->category = category;
}

bool Item::isLowStock() const
{
    return quantity <= threshold;
}

std::string Item::toString() const
{
    std::ostringstream stream;
    stream << "ID: " << itemId << " | Name: " << name
           << " | Category: " << category
           << " | Qty: " << quantity
           << " | Price: $" << std::fixed << std::setprecision(2) << price
           << " | Threshold: " << threshold;
    return stream.str();
}