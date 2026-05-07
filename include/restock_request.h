#pragma once

#include <string>

class RestockRequest
{
private:
    std::string requestId;
    std::string itemId;
    std::string itemName;
    int currentQuantity;
    int requestedQuantity;
    std::string timestamp;

public:
    RestockRequest(const std::string &requestId,
                   const std::string &itemId,
                   const std::string &itemName,
                   int currentQuantity,
                   int requestedQuantity,
                   const std::string &timestamp);

    const std::string &getRequestId() const;
    const std::string &getItemId() const;
    const std::string &getItemName() const;
    int getCurrentQuantity() const;
    int getRequestedQuantity() const;
    const std::string &getTimestamp() const;
};
