#ifndef RESTOCKREQUEST_H
#define RESTOCKREQUEST_H

class RestockRequest
{
private:
    int itemID;
    int suggestedQty;

public:
    RestockRequest(int id, int qty);

    int getItemID() const;
    int getSuggestedQty() const;
};

#endif