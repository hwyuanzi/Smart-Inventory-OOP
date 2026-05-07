#pragma once

#include <string>
using namespace std;

class Transaction
{
    /*
     * Saved sale details.
     */
private:
    string transactionId;
    string itemId;
    string itemName;
    int quantity;
    double totalPrice;
    string timestamp;

    /*
     * Create a transaction record after a sale succeeds.
     */
public:
    Transaction(const string &transactionId,
                const string &itemId,
                const string &itemName,
                int quantity,
                double totalPrice,
                const string &timestamp);

    /*
     * Read transaction fields.
     */
    const string &getTransactionId() const;
    const string &getItemId() const;
    const string &getItemName() const;
    int getQuantity() const;
    double getTotalPrice() const;
    const string &getTimestamp() const;
};
