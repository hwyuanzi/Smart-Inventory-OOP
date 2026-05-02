#include <string>
#include <vector>
#include "item.h"
using namespace std;

class Inventory
{
private:
    vector<Item> items;

public:
    void addItem(const Item &item);
    void removeItem(int id);
    void display() const;
    bool updateItem(int id, string name, int quantity, double price);
    Item *searchItem(int id);
};