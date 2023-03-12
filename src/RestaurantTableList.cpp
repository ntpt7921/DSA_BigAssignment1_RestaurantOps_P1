#include "RestaurantTableList.h"
#include <iostream>

// return nullptr if there is no free table group, else return pointer to start of group
// find a group of table with size groupSize, whose starting table have max tableID
SingleLinkedNode<RestaurantTable>* 
RestaurantTableList::searchFreeGroupTableStartWithMaxID(int groupSize)
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


RestaurantTableList::RestaurantTableList(int numTable):
    CircularLinkedList<RestaurantTable>()
{
    for (int i = 0; i < numTable; i++)
        this->insertAtEnd(RestaurantTable(Customer(), i + 1));
}

bool RestaurantTableList::isAllFull()
{
    return (occupiedTableCount >= this->size);
}

bool RestaurantTableList::alreadyHaveGroupTable()
{
    return this->haveGroupTable;
}

// return nullptr if there is no free table
RestaurantTable* RestaurantTableList::getFreeSingleTableFromIndex(int index)
{
    if (occupiedTableCount >= this->size)
        return nullptr;
    
    // test if the table at index is free
    SingleLinkedNode<RestaurantTable> *currTable = this->atNode(index);
    if (currTable == nullptr)
        return nullptr;
    if (currTable->data.isFree)
    {
        mostRecentlyChangedTableID = currTable->data.tableID;
        occupiedTableCount++;
        return &(currTable->data);
    }

    // if not free, start testing subsequent table until a free one is found
    int numTableTested = 1;
    currTable = currTable->next;
    while (numTableTested < this->size)
    {
        if (currTable->data.isFree)
        {
            mostRecentlyChangedTableID = currTable->data.tableID;
            occupiedTableCount++;
            return &(currTable->data);
        }

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
RestaurantTable* RestaurantTableList::getFreeGroupTable(int groupSize)
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

        mostRecentlyChangedTableID = groupStart->data.tableID;
        occupiedTableCount += groupSize;
        return &(groupStart->data);
    }
}

RestaurantTable *RestaurantTableList::cleanTable(int index)
{
    SingleLinkedNode<RestaurantTable> *toClean = this->atNode(index);
    if (toClean == nullptr)
        return nullptr;

    // do nothing if table is already free
    if (toClean->data.isFree)
        return nullptr;

    SingleLinkedNode<RestaurantTable> *result = toClean;

    if (!toClean->data.isWithinGroup)
    {
        // starting table, disassemble the group into single table and free
        if (toClean->data.orderWithinGroup == 0)
        {
            do {
                toClean->data.isWithinGroup = false;
                toClean->data.orderWithinGroup = -1;
                toClean->data.isFree = true;
                toClean = toClean->next;
                this->occupiedTableCount--;
            } while (toClean->data.isWithinGroup);
        }
    }
    else // is single table
    {
        toClean->data.isFree = true;
        this->occupiedTableCount--;
    }

    this->mostRecentlyChangedTableID = result->data.tableID;
    return &(result->data);
}


void RestaurantTableList::printSeatedTableFromMostRecentlySeated()
{
    SingleLinkedNode<RestaurantTable> *curr = this->atNode(mostRecentlyChangedTableID - 1);

    for (int i = 0; i < this->size; i++)
    {
        if (curr->data.isFree)
            std::cout << curr->data.tableID << '-' << "Empty" << '\n';
        else
            std::cout << curr->data.tableID << '-' << curr->data.customerInfo.name << '\n';

        curr = curr->next;
    }
}
