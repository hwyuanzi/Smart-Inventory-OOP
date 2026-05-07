#pragma once

#include <string>
using namespace std;

class RestockRequest
{
    /*
     * Private Attributes
     */
private:
    string requestId;
    string itemId;
    string itemName;
    int currentQuantity;
    int requestedQuantity;
    string timestamp;

public:
    /*
     * Public Constructor
     */
    RestockRequest(const string &requestId,
                   const string &itemId,
                   const string &itemName,
                   int currentQuantity,
                   int requestedQuantity,
                   const string &timestamp);

    /*
     * Getter Methods
     */
    const string &getRequestId() const;
    const string &getItemId() const;
    const string &getItemName() const;
    int getCurrentQuantity() const;
    int getRequestedQuantity() const;
    const string &getTimestamp() const;
};
