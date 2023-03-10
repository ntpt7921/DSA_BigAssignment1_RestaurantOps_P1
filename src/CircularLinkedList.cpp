#include "CircularLinkedList.h"

template <typename T>
SingleLinkedNode<T> * CircularLinkedList<T>::atNode(int index)
{
    if (this->size == 0)
        return nullptr;

    SingleLinkedNode<T> *result = this->head;
    for (int i = 0; i < index; i++)
        result = result->next;

    return result;
}


template <typename T>
CircularLinkedList<T>::CircularLinkedList():
    head(nullptr), tail(nullptr), size(0)
{}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList()
{
    SingleLinkedNode<T> *curr = head;
    while (curr != nullptr)
    {
        auto temp = curr;
        curr = curr->next;
        delete temp;
    }
}

template <typename T>
void CircularLinkedList<T>::insertAt(const T &d, int index)
{
    if (index > this->size || index < 0)
        return;

    SingleLinkedNode<T> *newNode = new SingleLinkedNode<T>(d, nullptr);

    if (this->size == 0)
    {
        this->head = this->tail = newNode;
        newNode->next = newNode;
    }
    else
    {
        if (index == 0)
        {
            newNode->next = this->head;
            this->tail->next = newNode;
            this->head = newNode;
        }
        else if (index == this->size)
        {
            this->tail->next = newNode;
            newNode->next = this->head;
            this->tail = newNode;
        }
        else
        {
            SingleLinkedNode<T> *before = this->atNode(index - 1);
            SingleLinkedNode<T> *after = before->next;
            before->next = newNode;
            newNode->next = after;
        }
    }
    this->size++;
}

template <typename T>
void CircularLinkedList<T>::insertAtEnd(const T &d)
{
    this->insertAt(d, this->size);
}

template <typename T>
void CircularLinkedList<T>::insertAtStart(const T &d)
{
    this->insertAt(d, 0);
}

// return the pointer to the node after deletion point
template <typename T>
SingleLinkedNode<T> * CircularLinkedList<T>::deleteAt(int index)
{
    if (index < 0 || index > this->size - 1)
        return nullptr;

    SingleLinkedNode<T> *toDelete = nullptr;
    if (this->size == 0)
        return nullptr;
    else if (this->size == 1)
    {
        toDelete = this->head;
        this->head = this->tail = nullptr;
    }
    else
    {
        if (index == 0)
        {
            toDelete = this->head;
            this->tail->next = this->head->next;
            this->head = this->head->next;
        }
        else if (index == this->size - 1)
        {
            toDelete = this->tail;
            SingleLinkedNode<T> *beforeEnd = this->at(index - 1);
            beforeEnd->next = this->head;
            this->tail = beforeEnd;
        }
        else
        {
            SingleLinkedNode<T> *before = this->at(index - 1);
            toDelete = before->next;
            before->next = toDelete->next;
        }
    }

    this->size--;
    SingleLinkedNode<T> *result = toDelete->next;
    delete toDelete;

    return result;
}

template <typename T>
SingleLinkedNode<T> * CircularLinkedList<T>::deleteAtStart()
{
    return this->deleteAt(0);
}

template <typename T>
SingleLinkedNode<T> * CircularLinkedList<T>::deleteAtEnd()
{
    return this->deleteAt(this->size - 1);
}

template <typename T>
typename CircularLinkedList<T>::Iterator
CircularLinkedList<T>::deleteAt(const Iterator &iter)
{
    Iterator result = iter;
    result++;

    this->deleteAt(iter.index);

    return result;
}

template <typename T>
typename CircularLinkedList<T>::Iterator
CircularLinkedList<T>::begin()
{
    Iterator iter;
    iter.container = this;
    iter.index = 0;
    iter.curr = this->head;
}

template <typename T>
typename CircularLinkedList<T>::Iterator
CircularLinkedList<T>::end()
{
    Iterator iter;
    iter.container = this;
    iter.index = this->size;
    iter.curr = this->tail;
}

template <typename T>
CircularLinkedList<T>::Iterator::Iterator()
{}

template <typename T>
CircularLinkedList<T>::Iterator::Iterator(const Iterator &iter):
    container(iter.container), index(iter.index), currNode(iter.currNode)
{}

template <typename T>
CircularLinkedList<T>::Iterator::~Iterator()
{}

template <typename T>
typename CircularLinkedList<T>::Iterator&
CircularLinkedList<T>::Iterator::operator=(const Iterator &iter)
{
    this->container = iter.container;
    this->index = iter.index;
    this->currNode = iter.currNode;

    return *this;
}

template <typename T>
typename CircularLinkedList<T>::Iterator&
CircularLinkedList<T>::Iterator::operator++()
{
    this->currNode = this->currNode->next;
    this->index++;

    return *this;
}

template <typename T>
typename CircularLinkedList<T>::Iterator&
CircularLinkedList<T>::Iterator::operator++(int)
{
    CircularLinkedList<T>::Iterator result(*this);
    (*this)++;

    return *result;
}

template <typename T>
T&
CircularLinkedList<T>::Iterator::operator*()
{
    return this->currNode->data;
}

template <typename T>
T*
CircularLinkedList<T>::Iterator::operator->()
{
    return &(this->currNode->data);
}

template <typename T>
bool 
CircularLinkedList<T>::Iterator::operator==(
        const typename CircularLinkedList<T>::Iterator &iter)
{
    return (this->container == iter.container) &&
        (this->currNode == iter.currNode) &&
        (this->index == iter.index);
}

template <typename T>
bool 
CircularLinkedList<T>::Iterator::operator!=(
        const typename CircularLinkedList<T>::Iterator &iter)
{
    return !(*this == iter);
}
