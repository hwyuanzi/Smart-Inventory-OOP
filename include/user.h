#ifndef USER_H
#define USER_H

class Inventory;

class User
{
public:
    virtual void menu(Inventory &inventory) = 0;
    virtual ~User() {}
};

#endif