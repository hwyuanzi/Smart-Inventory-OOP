#include "restock_request.h"

RestockRequest::RestockRequest(const std::string &requestId,
                               const std::string &itemId,
                               const std::string &itemName,
                               int currentQuantity,
                               int requestedQuantity,
                               const std::string &timestamp)
    : requestId(requestId),
      itemId(itemId),
      itemName(itemName),
      currentQuantity(currentQuantity),
      requestedQuantity(requestedQuantity),
      timestamp(timestamp) {}

const std::string &RestockRequest::getRequestId() const
{
    return requestId;
}

const std::string &RestockRequest::getItemId() const
{
    return itemId;
}

const std::string &RestockRequest::getItemName() const
{
    return itemName;
}

int RestockRequest::getCurrentQuantity() const
{
    return currentQuantity;
}

int RestockRequest::getRequestedQuantity() const
{
    return requestedQuantity;
}

const std::string &RestockRequest::getTimestamp() const
{
    return timestamp;
}
