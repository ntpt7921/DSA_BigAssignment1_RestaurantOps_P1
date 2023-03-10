#include "main.h"
#include <string>

struct Customer
{
    int requestTableID = 0;
    int receivedTableID = 0;
    string name;
    int age = 0;
};

template <typename T>
class SingleLinkedNode
{
public:
    T data;
    SingleLinkedNode<T> *next;
    
    SingleLinkedNode(): 
        next(nullptr) 
    {}

    SingleLinkedNode(const T &_data, SingleLinkedNode<T> *_next):
        data(_data), next(_next)
    {}
};

template <typename T>
class Iterator
{
};

template <typename T>
class CircularLinkedList
{
protected:
    SingleLinkedNode<T> *head, *tail; 
    int size; 

    SingleLinkedNode<T> *atNode(int index)
    {
        if (this->size == 0)
            return nullptr;

        SingleLinkedNode<T> *result = this->head;
        for (int i = 0; i < index; i++)
            result = result->next;

        return result;
    }

public:
    CircularLinkedList():
        head(nullptr), tail(nullptr), size(0)
    {}

    ~CircularLinkedList()
    {
        SingleLinkedNode<T> *curr = head;
        while (curr != nullptr)
        {
            auto temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    
    void insertAt(const T &d, int index)
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

    void insertAtEnd(const T &d)
    {
        this->insertAt(d, this->size);
    }

    void insertAtStart(const T &d)
    {
        this->insertAt(d, 0);
    }

    // return the pointer to the node after deletion point
    SingleLinkedNode<T> *deleteAt(int index)
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

    SingleLinkedNode<T> *deleteAtStart()
    {
        return this->deleteAt(0);
    }

    SingleLinkedNode<T> *deleteAtEnd()
    {
        return this->deleteAt(this->size - 1);
    }
};

template <typename T>
class Stack: public CircularLinkedList<T>
{
public:

    Stack(): 
        CircularLinkedList<T>()
    {}

    ~Stack()
    {}

    void push(const T &d)
    {
        this->insertAtStart(d);
        if (this->size > MAXSIZE)
            this->deleteAtEnd();
    }

    void pop()
    {
        this->deleteAtStart();
    }

    T &top()
    {
        return this->head->data; 
    }
};

template <typename T>
class Queue: public CircularLinkedList<T>
{
protected:
public:
    Queue():
        CircularLinkedList<T>()
    {}

    ~Queue()
    {}

    void enqueue(const T &d)
    {
        this->insertAtEnd(d);
    }

    void dequeue()
    {
        this->deleteAtStart();
    }

    T &front()
    {
        return this->head->data;
    }

    T &back()
    {
        return this->tail->data;
    }
};

class CustomerPresentStack: public Stack<Customer>
{
public:
    CustomerPresentStack(): 
        Stack<Customer>()
    {}

    void printRecentHistory(int numEntry)
    {
        if (this->size == 0)
        {
            std::cout << "Empty\n";
            return;
        }

        SingleLinkedNode<Customer> *curr = this->head;
        for (int i = 0; i < numEntry && i < this->size; i++)
        {
            std::cout << curr->data.name << '\n';
            curr = curr->next;
        }
    }

    void removeCustomer(const Customer &c)
    {
    }
};

class CustomerWaitingQueue: public Queue<Customer>
{
public:
    CustomerWaitingQueue():
        Queue<Customer>()
    {}

    // print customer in the queue from earliest (front) to latest (back)
    void printWaitingCustomer(int numCustomer)
    {
        if (this->size == 0)
        {
            std::cout << "Empty\n";
            return;
        }

        SingleLinkedNode<Customer> *curr = this->head;
        for (int i = 0; i < numCustomer && i < this->size; i++)
        {
            std::cout << curr->data.name << '\n';
            curr = curr->next;
        }
    }

    // use selection sort to push numCustomer oldest within queue to the front
    // this will not be a stable parital sort
    // NOTE: also print the queue afterward, but not sure how
    void prioritizeOldest(int numCustomer)
    {
        if (this->size == 0)
        {
            std::cout << "Empty\n"; 
            return;
        }

        SingleLinkedNode<Customer> *curr = this->head;
        for (int i = 0; i < numCustomer; i++)
        {
            SingleLinkedNode<Customer> *maxAgeCustomer = curr;
            for (auto customer = curr->next; customer != nullptr; customer = customer->next)
                if (maxAgeCustomer->data.age < customer->data.age)
                    maxAgeCustomer = customer;

            std::swap(maxAgeCustomer->data, curr->data);

            curr = curr->next;
        }

        printWaitingCustomer(MAXSIZE); // may print it like this, may change later
    }
};

struct RestaurantTable
{
    Customer customerInfo; 
    int tableID = 0;
    bool isWithinGroup = false;
    int orderWithinGroup = -1; // start from 0 for a table within group, else keep -1
    bool isFree = true;

    RestaurantTable(const Customer &_customerInfo, int _tableID, 
                    bool _isWithinGroup = true, int _orderWithinGroup = -1, bool _isFree = true):
        customerInfo(_customerInfo), tableID(_tableID), 
        isWithinGroup(_isWithinGroup), orderWithinGroup(_orderWithinGroup), isFree(_isFree)
    {}
};

class RestaurantTableList: public CircularLinkedList<RestaurantTable>
{
private:
    int occupiedTableCount = 0;
    bool haveGroupTable = false;

    // return nullptr if there is no free table group, else return pointer to start of group
    // find a group of table with size groupSize, whose starting table have max tableID
    SingleLinkedNode<RestaurantTable> *searchFreeGroupTableStartWithMaxID(int groupSize)
    {
        SingleLinkedNode<RestaurantTable> *foundGroupAt = nullptr;

        // try to search for table group with max starting table ID
        // have to add a counter so that we know when to stop (this is a circular linked list)
        SingleLinkedNode<RestaurantTable> *curr = this->head;
        for (int testedGroupCount = 0; 
                testedGroupCount < this->size; 
                testedGroupCount++, curr = curr->next)
        {
            if (!curr->data.isFree)
                continue;

            bool groupValid = true;
            SingleLinkedNode<RestaurantTable> *test = curr->next;
            int orderWithinGroup = 1;
            for ( ; orderWithinGroup < groupSize;
                    orderWithinGroup++, test = test->next)
            {
                if (!test->data.isFree)
                {
                    groupValid = false;
                    break;
                }
            }

            if (groupValid)
            {
                if (foundGroupAt == nullptr)
                    foundGroupAt = curr;
                else if (foundGroupAt->data.tableID < curr->data.tableID)
                    foundGroupAt = curr;
            }
            else
            {
                curr = test;
                testedGroupCount += orderWithinGroup;
            }
        }


        if (foundGroupAt == nullptr)
            return nullptr;
        else
            return foundGroupAt;
    }

public:
    RestaurantTableList(int numTable = 0):
        CircularLinkedList<RestaurantTable>()
    {
        for (int i = 0; i < numTable; i++)
            this->insertAt(RestaurantTable(Customer(), i + 1), this->size);
    }

    bool isAllFull()
    {
        return (occupiedTableCount >= this->size);
    }

    bool alreadyHaveGroupTable()
    {
        return this->haveGroupTable;
    }

    // return nullptr if there is no free table
    RestaurantTable *getFreeSingleTableFromIndex(int index)
    {
        if (occupiedTableCount >= this->size)
            return nullptr;
        
        // test if the table at index is free
        SingleLinkedNode<RestaurantTable> *currTable = this->atNode(index);
        if (currTable == nullptr)
            return nullptr;
        if (currTable->data.isFree)
            return &(currTable->data);

        // if not free, start testing subsequent table until a free one is found
        int numTableTested = 1;
        currTable = currTable->next;
        while (numTableTested < this->size)
        {
            if (currTable->data.isFree)
                return &(currTable->data);

            currTable = currTable->next;
            numTableTested++;
        }

        // since we tested for free table at the start of method
        // there should always be a free table, so not supposed to reach this
        return nullptr;
    }

    // result nullptr if no group table is possible, else return pointer to starting table of group
    // if there is possible group, all table within that group is grouped together
    // the grouping is noted as isWithinGroup and orderWithinGroup properties of RestaurantTable
    RestaurantTable *getFreeGroupTable(int groupSize)
    {
        if (this->haveGroupTable)
            return nullptr;

        SingleLinkedNode<RestaurantTable> *groupStart = 
            this->searchFreeGroupTableStartWithMaxID(groupSize);

        if (groupStart == nullptr)
            return nullptr;
        else
        {
            this->haveGroupTable = true;
            // all the table within group is modified to note that they belong to a group
            SingleLinkedNode<RestaurantTable> *curr = groupStart;
            for (int i = 0; i < groupSize; i++, curr = curr->next)
            {
                curr->data.isWithinGroup = true;
                curr->data.orderWithinGroup = i;
                curr->data.isFree = false;
            }
            // starting table represent the state of the whole group, so its isFree is left true
            groupStart->data.isFree = true;

            return &(groupStart->data);
        }
    }

    void cleanTable(int index)
    {
        SingleLinkedNode<RestaurantTable> *toClean = this->atNode(index);
        if (toClean == nullptr)
            return;

        // do nothing if table is already free
        if (toClean->data.isFree)
            return;

        if (toClean->data.isWithinGroup)
        {
            // starting table, disassemble the group into single table and free
            if (toClean->data.orderWithinGroup == 0)
            {
                do {
                    toClean->data.isWithinGroup = false;
                    toClean->data.orderWithinGroup = -1;
                    toClean->data.isFree = true;
                    toClean = toClean->next;
                } while (toClean->data.isWithinGroup);
            }
            // inner table of a group, do nothing
            else return;
        }
        else // is single table
        {
            toClean->data.isFree = true;
        }
    }
};

class CommandReader
{
private:
    std::ifstream commandFile;

    bool isSpaceChar(char c)
    {
        switch (c)
        {
            case ' ':
            case '\t':
            case '\n':
            case '\v':
            case '\f':
            case '\r':
                return true;
            default:
                return false;
        }

        return false;
    }

    CircularLinkedList<string> * tokenizeLine(const string &line)
    {
        static const string spaceCharList = " \t\n\v\f\r";

        CircularLinkedList<string> *result = new CircularLinkedList<string>();
        bool expectSpaceTokenNext = this->isSpaceChar(line[0]);

        if (line.empty())
            return result;

        string::size_type start = 0, end = string::npos;
        while (true)
        {
            if (expectSpaceTokenNext)
            {
                end = line.find_first_not_of(spaceCharList, start);
                // don't output space as token, so no format testing
                // result->insertAtEnd(line.substr(start, end));
            }
            else
            {
                end = line.find_first_of(spaceCharList, start);
                result->insertAtEnd(line.substr(start, end));
            }

            if (end == string::npos)
                break;
            expectSpaceTokenNext = !expectSpaceTokenNext;
            start = end;
        }
        return result;
    }

public:
    CircularLinkedList<string> * getNextCommandAsTokenList()
    {
        string line;
        if (this->canContinueReading())
            std::getline(commandFile, line);

        return tokenizeLine(line);
    }

    CommandReader(string _fileName):
        commandFile(_fileName, std::ios::in)
    {
        if (!commandFile.is_open())
            throw "CommandReader::constructor(string) - "
                  "Fail to open file with provided name";
    }

    ~CommandReader()
    {
        commandFile.close();
    }

    bool canContinueReading()
    {
        return (!commandFile); // no EOF or error has happened
    }
};

enum class CommandType
{
    REG,
    REGM,
    CLE,
    PS,
    PQ,
    SQ,
};

void simulate(string filename, restaurant* r)
{
}

