#pragma once

#include <string>

class Transaction
{
private:
    std::string transactionId;
    std::string itemId;
    std::string itemName;
    int quantity;
    double totalPrice;
    std::string timestamp;

public:
    Transaction(const std::string &transactionId,
                const std::string &itemId,
                const std::string &itemName,
                int quantity,
                double totalPrice,
                const std::string &timestamp);

    const std::string &getTransactionId() const;
    const std::string &getItemId() const;
    const std::string &getItemName() const;
    int getQuantity() const;
    double getTotalPrice() const;
    const std::string &getTimestamp() const;
};
