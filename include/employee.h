#pragma once

#include "user.h"

class Employee : public User
{
public:
    explicit Employee(const std::string &username);
    void menu() const override;
};
