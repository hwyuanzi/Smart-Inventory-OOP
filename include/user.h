#pragma once

#include <string>
using namespace std;

class User
{
    /*
     * Protected Attributes
     */
protected:
    string username;
    string password;
    string role;

public:
    /*
     * Public Constructor
     */
    User(const string &username, const string &password, const string &role);

    /*
     * Virtual Methods
     */
    virtual ~User() = default;
    virtual void displayMenu() const = 0;
    virtual string getRoleDisplay() const = 0;

    /*
     * Getter Methods
     */
    const string &getUsername() const;
    const string &getRole() const;

    bool authenticate(const string &pwd) const;
};