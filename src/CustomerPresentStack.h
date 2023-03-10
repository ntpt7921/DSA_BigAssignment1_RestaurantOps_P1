#ifndef CUSTOMERPRESENTSTACK
#define CUSTOMERPRESENTSTACK

#include "Customer.h"
#include "Stack.h"

class CustomerPresentStack: public Stack<Customer>
{
public:
    CustomerPresentStack();

    void printRecentHistory(int numEntry);
    void removeCustomer(const Customer &c);
};

#endif
