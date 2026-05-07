#include "transaction.h"
#include <string>
using namespace std;

/*
 * Parameterized constructor for creating a Transaction object.
 * Initializes transaction details including transaction ID,
 * item info (ID, name), quantity purchased, total price,
 * and the transaction timestamp.
 */
Transaction::Transaction(const string &transactionId,
                         const string &itemId,
                         const string &itemName,
                         int quantity,
                         double totalPrice,
                         const string &timestamp)
    : transactionId(transactionId),
      itemId(itemId),
      itemName(itemName),
      quantity(quantity),
      totalPrice(totalPrice),
      timestamp(timestamp) {}

/*
 * Getter Methods
 */
const string &Transaction::getTransactionId() const
{
    return transactionId;
}

const string &Transaction::getItemId() const
{
    return itemId;
}

const string &Transaction::getItemName() const
{
    return itemName;
}

int Transaction::getQuantity() const
{
    return quantity;
}

double Transaction::getTotalPrice() const
{
    return totalPrice;
}

const string &Transaction::getTimestamp() const
{
    return timestamp;
}
