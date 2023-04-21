#ifndef CUSTOMERWAITINGQUEUE
#define CUSTOMERWAITINGQUEUE

#include "Customer.h"
#include "Queue.h"

class CustomerWaitingQueue : public Queue<Customer>
{
public:
    CustomerWaitingQueue();

    // print customer in the queue from earliest (front) to latest (back)
    void printWaitingCustomer(int numCustomer);

    // use selection sort to push numCustomer oldest within queue to the front
    // this will not be a stable parital sort
    // NOTE: also print the queue afterward, but not sure how
    void prioritizeOldest(int numCustomer);
};

#endif
