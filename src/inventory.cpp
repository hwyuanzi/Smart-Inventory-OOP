#include "inventory.h"

#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

/*
 * Normalize text before matching names or IDs.
 */
string Inventory::toLower(const std::string &text)
{
    string lower = text;
    transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch)
              { return static_cast<char>(tolower(ch)); });
    return lower;
}

/*
 * Restock request IDs start fresh for each program run.
 */
Inventory::Inventory() : nextRestockId(1) {}

/*
 * Append a new item to the in-memory inventory.
 */
void Inventory::addItem(const Item &item)
{
    items.push_back(item);
}

/*
 * Delete the item and clean up any pending restock request for it.
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
 * Find the stored item with this ID, or return nullptr when it is missing.
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
 * Match a query against item names and IDs without caring about case.
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
 * Expose the item list for menu display and simple reports.
 */
vector<Item> &Inventory::getAllItems()
{
    return items;
}

/*
 * Update editable item details. Quantity is handled separately.
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
 * Set the stock count after validating the item and the new quantity.
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
 * Collect items that have hit their restock threshold.
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
 * Keep only one open restock request per item.
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
 * Expose the pending restock queue to manager workflows.
 */
vector<RestockRequest> &Inventory::getRestockRequests()
{
    return restockRequests;
}

/*
 * Clear the pending restock request for an item after it is handled.
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
 * Use short, readable request IDs in the CLI output.
 */
string Inventory::generateRestockId()
{
    return "R" + to_string(nextRestockId++);
}