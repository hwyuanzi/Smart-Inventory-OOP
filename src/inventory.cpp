#include "inventory.h"

#include <algorithm>
#include <cctype>

std::string Inventory::toLower(const std::string &text)
{
    std::string lower = text;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return lower;
}

Inventory::Inventory() : nextRestockId(1) {}

void Inventory::addItem(const Item &item)
{
    items.push_back(item);
}

bool Inventory::removeItem(const std::string &itemId)
{
    auto itemIt = std::remove_if(items.begin(), items.end(), [&itemId](const Item &item) {
        return item.getItemId() == itemId;
    });
    if (itemIt == items.end())
    {
        return false;
    }
    items.erase(itemIt, items.end());
    clearRestockRequest(itemId);
    return true;
}

Item *Inventory::findItem(const std::string &itemId)
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

std::vector<Item *> Inventory::searchByName(const std::string &query)
{
    std::vector<Item *> matches;
    const std::string key = toLower(query);
    for (Item &item : items)
    {
        const std::string nameKey = toLower(item.getName());
        const std::string idKey = toLower(item.getItemId());
        if (nameKey.find(key) != std::string::npos || idKey.find(key) != std::string::npos)
        {
            matches.push_back(&item);
        }
    }
    return matches;
}

std::vector<Item> &Inventory::getAllItems()
{
    return items;
}

bool Inventory::updateItem(const std::string &id, const std::string &name, double price, int threshold, const std::string &category)
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

bool Inventory::updateStockQuantity(const std::string &id, int qty)
{
    Item *item = findItem(id);
    if (item == nullptr || qty < 0)
    {
        return false;
    }
    item->setQuantity(qty);
    return true;
}

std::vector<Item *> Inventory::getLowStockItems()
{
    std::vector<Item *> lowStockItems;
    for (Item &item : items)
    {
        if (item.isLowStock())
        {
            lowStockItems.push_back(&item);
        }
    }
    return lowStockItems;
}

void Inventory::addRestockRequest(const RestockRequest &request)
{
    restockRequests.push_back(request);
}

std::vector<RestockRequest> &Inventory::getRestockRequests()
{
    return restockRequests;
}

bool Inventory::clearRestockRequest(const std::string &itemId)
{
    auto requestIt = std::remove_if(restockRequests.begin(), restockRequests.end(), [&itemId](const RestockRequest &request) {
        return request.getItemId() == itemId;
    });
    if (requestIt == restockRequests.end())
    {
        return false;
    }
    restockRequests.erase(requestIt, restockRequests.end());
    return true;
}

std::string Inventory::generateRestockId()
{
    return "R" + std::to_string(nextRestockId++);
}
