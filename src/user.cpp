#include "user.h"

User::User(const std::string &username, const std::string &password, const std::string &role)
    : username(username), password(password), role(role) {}

const std::string &User::getUsername() const
{
    return username;
}

const std::string &User::getRole() const
{
    return role;
}

bool User::authenticate(const std::string &pwd) const
{
    return pwd == password;
}