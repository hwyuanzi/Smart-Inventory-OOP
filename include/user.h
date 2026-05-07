#pragma once

#include <string>

class User
{
protected:
    std::string username;
    std::string password;
    std::string role;

public:
    User(const std::string &username, const std::string &password, const std::string &role);
    virtual ~User() = default;
    const std::string &getUsername() const;
    const std::string &getRole() const;
    bool authenticate(const std::string &pwd) const;
    virtual void displayMenu() const = 0;
    virtual std::string getRoleDisplay() const = 0;
};