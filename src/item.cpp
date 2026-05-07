#include "item.h"

#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

/*
 * Parameterized constructor for creating an Item object.
 * Initializes all item attributes such as ID, name,
 * quantity, price, stock threshold, and category.
 */
Item::Item(const string &id, const string &name, int qty, double price, int thresh, const string &category)
    : itemId(id), name(name), quantity(qty), price(price), threshold(thresh), category(category) {}

/*
 * Getter Methods
 */
const string &Item::getItemId() const
{
    return itemId;
}

const string &Item::getName() const
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

const string &Item::getCategory() const
{
    return category;
}

/*
 * Setter Methods
 */

void Item::setName(const string &name)
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

void Item::setCategory(const string &category)
{
    this->category = category;
}

/*
 * Checks whether the item is considered low in stock.
 * Returns true if the quantity is less than or equal
 * to the threshold value; otherwise returns false.
 */
bool Item::isLowStock() const
{
    return quantity <= threshold;
}

/*
 * Converts the item object into a formatted string.
 * The returned string contains all important item
 * information including ID, name, category, quantity,
 * price (formatted to 2 decimal places), and threshold.
 */
string Item::toString() const
{
    ostringstream stream;
    stream << "ID: " << itemId << " | Name: " << name
           << " | Category: " << category
           << " | Qty: " << quantity
           << " | Price: $" << fixed << setprecision(2) << price
           << " | Threshold: " << threshold;
    return stream.str();
}