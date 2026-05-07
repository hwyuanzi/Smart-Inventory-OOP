#pragma once

#include <string>

class User
{
protected:
    std::string username;

public:
    explicit User(const std::string &username);
    virtual ~User() = default;
    virtual void menu() const = 0;

    const std::string &getUsername() const;
};