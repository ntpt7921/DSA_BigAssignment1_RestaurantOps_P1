#include "RestaurantTable.h"

RestaurantTable::RestaurantTable(const Customer &_customerInfo, int _tableID, 
                                 bool _isWithinGroup, int _orderWithinGroup, bool _isFree):
    customerInfo(_customerInfo), tableID(_tableID), 
    isWithinGroup(_isWithinGroup), orderWithinGroup(_orderWithinGroup), isFree(_isFree)
{}
