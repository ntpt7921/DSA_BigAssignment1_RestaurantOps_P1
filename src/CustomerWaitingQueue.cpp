#include "CustomerWaitingQueue.h"
#include "main.h"
#include <iostream>

CustomerWaitingQueue::CustomerWaitingQueue():
    Queue<Customer>()
{}

// print customer in the queue from earliest (front) to latest (back)
void CustomerWaitingQueue::printWaitingCustomer(int numCustomer)
{
    if (this->size == 0)
    {
        std::cout << "Empty\n";
        return;
    }

    Iterator curr = this->begin();
    for (int i = 0; i < numCustomer && i < this->size; i++)
    {
        std::cout << curr->name << '\n';
        curr++;
    }
}

// use selection sort to push numCustomer oldest within queue to the front
// this will not be a stable parital sort
// NOTE: also print the queue afterward, but not sure how
void CustomerWaitingQueue::prioritizeOldest(int numCustomer)
{
    if (this->size == 0)
    {
        std::cout << "Empty\n"; 
        return;
    }

    if (numCustomer > this->size)
        numCustomer  = this->size;

    Iterator curr = this->begin();
    for (int i = 0; i < numCustomer; i++)
    {
        Iterator maxAgeCustomer = curr, customer = curr;
        customer++;
        for ( ; customer != this->end(); customer++)
            if (maxAgeCustomer->age < customer->age)
                maxAgeCustomer = customer;

        std::swap(*maxAgeCustomer, *curr);

        curr++;
    }

    this->printWaitingCustomer(MAXSIZE); // may print it like this, may change later
}
