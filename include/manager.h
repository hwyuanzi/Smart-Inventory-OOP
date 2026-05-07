#pragma once

#include "user.h"

#include <string>

class Manager : public User
{
private:
    std::string password;

public:
    Manager(const std::string &username, const std::string &password);
    bool authenticate(const std::string &inputPassword) const;
    void menu() const override;
};
