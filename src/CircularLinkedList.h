#ifndef CIRCULARLINKEDLIST
#define CIRCULARLINKEDLIST

#include "SingleLinkedNode.h"

template <typename T>
class CircularLinkedList
{
protected:
    SingleLinkedNode<T> *head, *tail; 
    int size; 

    SingleLinkedNode<T> *atNode(int index);

public:
    class Iterator;

    CircularLinkedList();
    ~CircularLinkedList();
    
    void insertAt(const T &d, int index);
    void insertAtEnd(const T &d);
    void insertAtStart(const T &d);

    // return the pointer to the node after deletion point
    SingleLinkedNode<T> *deleteAt(int index);
    SingleLinkedNode<T> *deleteAtStart();
    SingleLinkedNode<T> *deleteAtEnd();
    Iterator deleteAt(const Iterator &iter);

    Iterator begin();
    Iterator end();

public:
    class Iterator
    {
    private:
        CircularLinkedList<T> *container = nullptr;
        int index = -1;
        SingleLinkedNode<T> *currNode = nullptr;

    public:
        Iterator();
        Iterator(const Iterator &iter);
        Iterator &operator=(const Iterator &iter); 

        ~Iterator();

        Iterator &operator++();
        Iterator &operator++(int);

        T &operator*();
        T *operator->();

        bool operator==(const Iterator &iter);
        bool operator!=(const Iterator &iter);
    };
};

#endif
