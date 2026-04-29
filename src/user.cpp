#include "user.h"
#include <string>

User::User(string name)
{
    this->username = username;
}

string User::getUsername() const
{
    return username;
}