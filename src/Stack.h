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

template <typename T>
Stack<T>::Stack(): 
    CircularLinkedList<T>()
{}

template <typename T>
Stack<T>::~Stack()
{}

template <typename T>
void Stack<T>::push(const T &d)
{
    this->insertAtStart(d);
    if (this->size > MAXSIZE)
        this->deleteAtEnd();
}

template <typename T>
void Stack<T>::pop()
{
    this->deleteAtStart();
}

template <typename T>
T& Stack<T>::top()
{
    return this->head->data; 
}

#endif
