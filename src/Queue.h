#ifndef QUEUE
#define QUEUE

#include "CircularLinkedList.h"

template <typename T>
class Queue: public CircularLinkedList<T>
{
protected:
public:
    Queue();
    ~Queue();

    void enqueue(const T &d);
    void dequeue();

    T &front();
    T &back();
};

#endif
