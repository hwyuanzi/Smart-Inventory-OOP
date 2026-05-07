#include "user.h"
#include <string>
using namespace std;

/*
 * Parameterized constructor for creating a User object.
 * Initializes the username, password, and role
 * associated with the user account.
 */
User::User(const string &username, const string &password, const string &role)
    : username(username), password(password), role(role) {}

/*
 * Getter Methods
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
 * Verifies whether the provided password
 * matches the stored user password.
 * Returns true if authentication succeeds;
 * otherwise returns false.
 */
bool User::authenticate(const string &pwd) const
{
    return pwd == password;
}