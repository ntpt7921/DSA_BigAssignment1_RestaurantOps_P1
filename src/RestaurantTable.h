#ifndef RESTAURANTTABLE
#define RESTAURANTTABLE

#include "Customer.h"

struct RestaurantTable
{
    Customer customerInfo; 
    int tableID = 0;
    bool isWithinGroup = false;
    int orderWithinGroup = -1; // start from 0 for a table within group, else keep -1
    bool isFree = true;

    RestaurantTable(const Customer &_customerInfo, int _tableID, 
            bool _isWithinGroup = false, int _orderWithinGroup = -1, bool _isFree = true);
};

#endif
