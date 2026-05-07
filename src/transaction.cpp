#include "transaction.h"

Transaction::Transaction(const std::string &transactionId,
                         const std::string &itemId,
                         const std::string &itemName,
                         int quantity,
                         double totalPrice,
                         const std::string &timestamp)
    : transactionId(transactionId),
      itemId(itemId),
      itemName(itemName),
      quantity(quantity),
      totalPrice(totalPrice),
      timestamp(timestamp) {}

const std::string &Transaction::getTransactionId() const
{
    return transactionId;
}

const std::string &Transaction::getItemId() const
{
    return itemId;
}

const std::string &Transaction::getItemName() const
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

const std::string &Transaction::getTimestamp() const
{
    return timestamp;
}
