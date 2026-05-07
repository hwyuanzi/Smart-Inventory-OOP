#include "restock_request.h"
#include <string>
using namespace std;

/*
 * Snapshot the item state at the time the restock request is opened.
 */
RestockRequest::RestockRequest(const string &requestId,
                               const string &itemId,
                               const string &itemName,
                               int currentQuantity,
                               int requestedQuantity,
                               const string &timestamp)
    : requestId(requestId),
      itemId(itemId),
      itemName(itemName),
      currentQuantity(currentQuantity),
      requestedQuantity(requestedQuantity),
      timestamp(timestamp) {}

/*
 * Basic request identifiers.
 */
const string &RestockRequest::getRequestId() const
{
    return requestId;
}

const string &RestockRequest::getItemId() const
{
    return itemId;
}

const string &RestockRequest::getItemName() const
{
    return itemName;
}

/*
 * Quantity on hand when the request was created.
 */
int RestockRequest::getCurrentQuantity() const
{
    return currentQuantity;
}

/*
 * Amount the manager should add when fulfilling this request.
 */
int RestockRequest::getRequestedQuantity() const
{
    return requestedQuantity;
}

/*
 * Creation time shown in reports if needed.
 */
const string &RestockRequest::getTimestamp() const
{
    return timestamp;
}
