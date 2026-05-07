#pragma once

#include <string>
using namespace std;

class Transaction
{
    /*
     * Private Attributes
     */
private:
    string transactionId;
    string itemId;
    string itemName;
    int quantity;
    double totalPrice;
    string timestamp;

    /*
     * Public Constructor
     */
public:
    Transaction(const string &transactionId,
                const string &itemId,
                const string &itemName,
                int quantity,
                double totalPrice,
                const string &timestamp);

    /*
     * Getter Methods
     */
    const string &getTransactionId() const;
    const string &getItemId() const;
    const string &getItemName() const;
    int getQuantity() const;
    double getTotalPrice() const;
    const string &getTimestamp() const;
};
