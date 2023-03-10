#ifndef STACK
#define STACK

#include "main.h"
#include "CircularLinkedList.h"

template <typename T>
class Stack: public CircularLinkedList<T>
{
public:

    Stack();
    ~Stack();

    void push(const T &d);
    void pop();

    T &top();
};

#endif
