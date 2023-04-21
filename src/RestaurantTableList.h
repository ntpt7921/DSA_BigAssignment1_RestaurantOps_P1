#ifndef RESTAURANTTABLELIST
#define RESTAURANTTABLELIST

#include "CircularLinkedList.h"
#include "RestaurantTable.h"

class RestaurantTableList : public CircularLinkedList<RestaurantTable>
{
private:
    int occupiedTableCount = 0;
    bool haveGroupTable = false;
    int mostRecentlyChangedTableID = 0;

    // return nullptr if there is no free table group, else return pointer to start of group
    // find a group of table with size groupSize, whose starting table have max tableID
    SingleLinkedNode<RestaurantTable> *searchFreeGroupTableStartWithMaxID(int groupSize);

public:
    RestaurantTableList(int numTable = 0);

    bool isAllFull();

    bool alreadyHaveGroupTable();

    // return nullptr if there is no free table
    RestaurantTable *getFreeSingleTableFromIndex(int index);

    // result nullptr if no group table is possible, else return pointer to starting table of group
    // if there is possible group, all table within that group is grouped together
    // the grouping is noted as isWithinGroup and orderWithinGroup properties of RestaurantTable
    RestaurantTable *getFreeGroupTable(int groupSize);

    RestaurantTable *cleanTable(int index);

    void printSeatedTableFromMostRecentlySeated();
};

#endif
