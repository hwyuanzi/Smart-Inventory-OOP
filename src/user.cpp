#include "user.h"
#include <string>
using namespace std;

/*
 * Base login fields shared by employees and managers.
 */
User::User(const string &username, const string &password, const string &role)
    : username(username), password(password), role(role) {}

/*
 * Account field accessors.
 */
const string &User::getUsername() const
{
    return username;
}

const string &User::getRole() const
{
    return role;
}

/*
 * Plain password check used by the CLI login flow.
 */
bool User::authenticate(const string &pwd) const
{
    return pwd == password;
}