#ifndef SINGLELINKEDNODE
#define SINGLELINKEDNODE

template <typename T>
class SingleLinkedNode
{
public:
    T data;
    SingleLinkedNode<T> *next;
    
    SingleLinkedNode();
    SingleLinkedNode(const T &_data, SingleLinkedNode<T> *_next);
};

template <typename T>
SingleLinkedNode<T>::SingleLinkedNode(): 
    next(nullptr) 
{}

template <typename T>
SingleLinkedNode<T>::SingleLinkedNode(const T &_data, SingleLinkedNode<T> *_next):
    data(_data), next(_next)
{}

#endif
