#include "user.h"
#include "inventory.h"

class Manager : public User
{
private:
    Inventory &inventory;

public:
    Manager(string username, Inventory &inventory);
    void menu() override;
    void addItem();
    void removeItem();
    void updateItem();
};