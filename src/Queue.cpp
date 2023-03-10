#include "Queue.h"

template <typename T>
Queue<T>::Queue():
    CircularLinkedList<T>()
{}

template <typename T>
Queue<T>::~Queue()
{}

template <typename T>
void Queue<T>::enqueue(const T &d)
{
    this->insertAtEnd(d);
}

template <typename T>
void Queue<T>::dequeue()
{
    this->deleteAtStart();
}

template <typename T>
T& Queue<T>::front()
{
    return this->head->data;
}

template <typename T>
T& Queue<T>::back()
{
    return this->tail->data;
}
