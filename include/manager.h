#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"

class Manager : public User
{
public:
    void menu(Inventory &inventory) override;

private:
    void handleAdd(Inventory &inventory);
    void handleDelete(Inventory &inventory);
    void handleRecordSale(Inventory &inventory);
};

#endif