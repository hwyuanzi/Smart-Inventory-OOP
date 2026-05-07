#include "restock_request.h"
#include <string>
using namespace std;

/*
 * Parameterized constructor for creating a RestockRequest object.
 * Initializes all request details including request ID,
 * item information, stock quantities, and timestamp.
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
 * Getter Methods
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
 * Returns the current stock quantity
 * of the item before restocking.
 */
int RestockRequest::getCurrentQuantity() const
{
    return currentQuantity;
}

/*
 * Returns the quantity requested
 * to be added to inventory.
 */
int RestockRequest::getRequestedQuantity() const
{
    return requestedQuantity;
}

/*
 * Returns the timestamp indicating when
 * the restock request was created.
 */
const string &RestockRequest::getTimestamp() const
{
    return timestamp;
}
