#include "restockReq.h"

RestockRequest::RestockRequest(int id, int qty)
{
    this->itemID = id;
    this->suggestedQty = qty;
}

int RestockRequest::getItemID() const
{
    return itemID;
}

int RestockRequest::getSuggestedQty() const
{
    return suggestedQty;
}
