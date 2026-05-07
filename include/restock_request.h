#pragma once

#include <string>
using namespace std;

class RestockRequest
{
    /*
     * Pending restock details.
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
     * Create a request when stock drops too low.
     */
    RestockRequest(const string &requestId,
                   const string &itemId,
                   const string &itemName,
                   int currentQuantity,
                   int requestedQuantity,
                   const string &timestamp);

    /*
     * Read request fields.
     */
    const string &getRequestId() const;
    const string &getItemId() const;
    const string &getItemName() const;
    int getCurrentQuantity() const;
    int getRequestedQuantity() const;
    const string &getTimestamp() const;
};
