#include <string>
using namespace std;

class User
{
    // protected attributes
protected:
    string username;

    // constructor
public:
    User(string username);
    virtual void menu() = 0;

    // getter method
    string getUsername() const;
};