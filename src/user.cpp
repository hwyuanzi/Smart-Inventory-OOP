#include "user.h"

User::User(const std::string &username) : username(username) {}

const std::string &User::getUsername() const
{
    return username;
}