#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "user.h"

class Employee : public User
{
public:
    void menu(Inventory &inventory) override;
};

#endif