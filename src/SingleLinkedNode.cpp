#include "SingleLinkedNode.h"

template <typename T>
SingleLinkedNode<T>::SingleLinkedNode(): 
    next(nullptr) 
{}

template <typename T>
SingleLinkedNode<T>::SingleLinkedNode(const T &_data, SingleLinkedNode<T> *_next):
    data(_data), next(_next)
{}
