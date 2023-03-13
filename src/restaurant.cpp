#include "CommandReader.h"
#include "Customer.h"
#include "CustomerPresentStack.h"
#include "CustomerWaitingQueue.h"
#include "RestaurantTableList.h"
#include "main.h"

#include <iostream>

void simulate(string filename, restaurant* r)
{
    r->recentTable = nullptr; // add this so no warning about unused variable emit

    CustomerWaitingQueue waitingQueue;
    CustomerPresentStack presentCustomerStack;
    RestaurantTableList tableList(MAXSIZE);

    try
    {
        CommandReader reader(filename);
        while (reader.canContinueReading())
        {
            Command currentCommand = reader.readNextCommand();
            if (!currentCommand.isValid())
                continue;
            else
                currentCommand.performEncodedOperation(tableList, presentCustomerStack, waitingQueue);
        }

    }
    catch (const char *message) 
    {
        std::cerr << message << std::endl;
    }
}

