#include "inventory.h"

#include <algorithm>
#include <cctype>
#include <iostream>

std::string Inventory::toLower(const std::string &text)
{
    std::string lower = text;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return lower;
}

bool Inventory::addItem(const Item &item)
{
    if (findItemById(item.getID()) != nullptr)
    {
        return false;
    }
    items.push_back(item);
    return true;
}

bool Inventory::deleteItemById(int id)
{
    auto it = std::remove_if(items.begin(), items.end(), [id](const Item &item) {
        return item.getID() == id;
    });
    if (it == items.end())
    {
        return false;
    }
    items.erase(it, items.end());
    return true;
}

Item *Inventory::findItemById(int id)
{
    for (Item &item : items)
    {
        if (item.getID() == id)
        {
            return &item;
        }
    }
    return nullptr;
}

const Item *Inventory::findItemById(int id) const
{
    for (const Item &item : items)
    {
        if (item.getID() == id)
        {
            return &item;
        }
    }
    return nullptr;
}

std::vector<const Item *> Inventory::searchItemsByName(const std::string &namePart) const
{
    std::vector<const Item *> matches;
    const std::string key = toLower(namePart);
    for (const Item &item : items)
    {
        if (toLower(item.getName()).find(key) != std::string::npos)
        {
            matches.push_back(&item);
        }
    }
    return matches;
}

bool Inventory::recordSale(int id, int quantitySold)
{
    Item *item = findItemById(id);
    if (item == nullptr || quantitySold <= 0 || quantitySold > item->getQuantity())
    {
        return false;
    }

    item->setQuantity(item->getQuantity() - quantitySold);
    return true;
}

bool Inventory::updateItemDetails(int id, const std::string &name, double price, int threshold)
{
    Item *item = findItemById(id);
    if (item == nullptr || price < 0 || threshold < 0)
    {
        return false;
    }

    item->setName(name);
    item->setPrice(price);
    item->setStockThreshold(threshold);
    return true;
}

bool Inventory::updateStockQuantity(int id, int quantity)
{
    Item *item = findItemById(id);
    if (item == nullptr || quantity < 0)
    {
        return false;
    }
    item->setQuantity(quantity);
    return true;
}

std::vector<const Item *> Inventory::getLowStockItems() const
{
    std::vector<const Item *> lowStockItems;
    for (const Item &item : items)
    {
        if (item.isLowStock())
        {
            lowStockItems.push_back(&item);
        }
    }
    return lowStockItems;
}

bool Inventory::isEmpty() const
{
    return items.empty();
}

void Inventory::displayAll() const
{
    if (items.empty())
    {
        std::cout << "Inventory is empty.\n";
        return;
    }

    for (const Item &item : items)
    {
        std::cout << "-------------------------\n";
        item.display();
    }
    std::cout << "-------------------------\n";
}
