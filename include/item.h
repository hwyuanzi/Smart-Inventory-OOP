#include <string>
using namespace std;

class Item
{
    // private attributes
private:
    int id;
    string name;
    int quantity;
    double price;

public:
    // class constructor
    Item(int id, string name, int quantity, double price);
    ~Item();

    // getter methods
    int getID() const;
    string getName() const;
    int getQuantity() const;
    double getPrice() const;

    // setter methods
    void setName(string name);
    void setQuantity(int quantity);
    void setPrice(double price);

    // display item details
    void display() const;
};