#ifndef CUSTOMER
#define CUSTOMER

#include <string>

struct Customer
{
    int requestTableID = 0;
    int receivedTableID = 0;
    std::string name;
    int age = 0;
};

#endif
