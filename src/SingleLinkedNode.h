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

#endif
