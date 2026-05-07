#pragma once

#include <string>
using namespace std;

class User
{
    /*
     * Shared account fields for all user roles.
     */
protected:
    string username;
    string password;
    string role;

public:
    /*
     * Set up a base user account.
     */
    User(const string &username, const string &password, const string &role);

    /*
     * Role-specific behavior supplied by subclasses.
     */
    virtual ~User() = default;
    virtual void displayMenu() const = 0;
    virtual string getRoleDisplay() const = 0;

    /*
     * Account accessors.
     */
    const string &getUsername() const;
    const string &getRole() const;

    bool authenticate(const string &pwd) const;
};