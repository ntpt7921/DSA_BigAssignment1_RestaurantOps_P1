#include "Stack.h"

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
