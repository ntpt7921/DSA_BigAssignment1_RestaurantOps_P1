#include "CustomerPresentStack.h"


CustomerPresentStack::CustomerPresentStack(): 
    Stack<Customer>()
{}

void CustomerPresentStack::printRecentHistory(int numEntry)
{
    if (this->size == 0)
    {
        std::cout << "Empty\n";
        return;
    }

    Iterator curr = this->begin();
    for (int i = 0; i < numEntry && i < this->size; i++)
    {
        std::cout << curr->name << '\n';
        curr++;
    }
}

void CustomerPresentStack::removeCustomer(const Customer &c)
{
    for (Iterator curr = this->begin(); curr != this->end(); curr++)
        if (c.receivedTableID == curr->receivedTableID)
        {
            this->deleteAt(curr);
            break;
        }
}
