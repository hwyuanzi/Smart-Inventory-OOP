#include "inventory.h"

#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

/*
 * Converts all characters in a string to lowercase.
 * Used to make searching case-insensitive so that
 * item names and IDs can be matched more easily.
 */
string Inventory::toLower(const std::string &text)
{
    string lower = text;
    transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch)
              { return static_cast<char>(tolower(ch)); });
    return lower;
}

/*
 * Default constructor for the Inventory class.
 * Initializes the restock request ID counter.
 */
Inventory::Inventory() : nextRestockId(1) {}

/*
 * Adds a new item object to the inventory list.
 */
void Inventory::addItem(const Item &item)
{
    items.push_back(item);
}

/*
 * Removes an item from the inventory using its ID.
 * Also removes any associated restock request
 * linked to the same item.
 *
 * Returns true if the item was found and removed;
 * otherwise returns false.
 */
bool Inventory::removeItem(const string &itemId)
{
    auto itemIt = remove_if(items.begin(), items.end(), [&itemId](const Item &item)
                            { return item.getItemId() == itemId; });
    if (itemIt == items.end())
    {
        return false;
    }
    items.erase(itemIt, items.end());
    clearRestockRequest(itemId);
    return true;
}

/*
 * Searches for an item by its ID.
 * Returns a pointer to the matching item if found;
 * otherwise returns nullptr.
 */
Item *Inventory::findItem(const string &itemId)
{
    for (Item &item : items)
    {
        if (item.getItemId() == itemId)
        {
            return &item;
        }
    }
    return nullptr;
}

/*
 * Searches the inventory for items whose name
 * or ID contains the given query string.
 * The search is case-insensitive.
 *
 * Returns a vector containing pointers to
 * all matching items.
 */
vector<Item *> Inventory::searchByName(const string &query)
{
    vector<Item *> matches;
    const string key = toLower(query);
    for (Item &item : items)
    {
        const string nameKey = toLower(item.getName());
        const string idKey = toLower(item.getItemId());
        if (nameKey.find(key) != string::npos || idKey.find(key) != string::npos)
        {
            matches.push_back(&item);
        }
    }
    return matches;
}

/*
 * Returns a reference to the vector
 * containing all inventory items.
 */
vector<Item> &Inventory::getAllItems()
{
    return items;
}

/*
 * Updates the main information of an item,
 * including its name, price, threshold,
 * and category.
 *
 * Returns true if the item exists and was updated;
 * otherwise returns false.
 */
bool Inventory::updateItem(const string &id, const string &name, double price, int threshold, const string &category)
{
    Item *item = findItem(id);
    if (item == nullptr)
    {
        return false;
    }
    item->setName(name);
    item->setPrice(price);
    item->setThreshold(threshold);
    item->setCategory(category);
    return true;
}

/*
 * Updates the stock quantity of a specific item.
 * Negative quantities are not allowed.
 *
 * Returns true if the update succeeds;
 * otherwise returns false.
 */
bool Inventory::updateStockQuantity(const string &id, int qty)
{
    Item *item = findItem(id);
    if (item == nullptr || qty < 0)
    {
        return false;
    }
    item->setQuantity(qty);
    return true;
}

/*
 * Retrieves all items that are currently
 * considered low in stock.
 *
 * Returns a vector containing pointers
 * to low-stock items.
 */
vector<Item *> Inventory::getLowStockItems()
{
    vector<Item *> lowStockItems;
    for (Item &item : items)
    {
        if (item.isLowStock())
        {
            lowStockItems.push_back(&item);
        }
    }
    return lowStockItems;
}

/*
 * Adds a new restock request to the system.
 * Prevents duplicate requests for the same item
 * by checking existing request entries first.
 */
void Inventory::addRestockRequest(const RestockRequest &request)
{
    for (const RestockRequest &existingRequest : restockRequests)
    {
        if (existingRequest.getItemId() == request.getItemId())
        {
            return;
        }
    }
    restockRequests.push_back(request);
}

/*
 * Returns a reference to the vector
 * containing all restock requests.
 */
vector<RestockRequest> &Inventory::getRestockRequests()
{
    return restockRequests;
}

/*
 * Removes a restock request associated
 * with a specific item ID.
 *
 * Returns true if a request was found and removed;
 * otherwise returns false.
 */
bool Inventory::clearRestockRequest(const std::string &itemId)
{
    auto requestIt = remove_if(restockRequests.begin(), restockRequests.end(), [&itemId](const RestockRequest &request)
                               { return request.getItemId() == itemId; });
    if (requestIt == restockRequests.end())
    {
        return false;
    }
    restockRequests.erase(requestIt, restockRequests.end());
    return true;
}

/*
 * Generates a unique restock request ID.
 * IDs are created sequentially in the format:
 * R1, R2, R3, ...
 */
string Inventory::generateRestockId()
{
    return "R" + to_string(nextRestockId++);
}