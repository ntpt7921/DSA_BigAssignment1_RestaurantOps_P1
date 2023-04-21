#ifndef COMMAND
#define COMMAND

#include "CustomerPresentStack.h"
#include "CustomerWaitingQueue.h"
#include "RestaurantTableList.h"
#include <string>

class Command
{
public:
    enum class CommandType
    {
        REG,
        REGM,
        CLE,
        PS,
        PQ,
        PT,
        SQ,
        INVALID,
    };

private:
    CommandType type;
    int ID;
    std::string name;
    int age;
    int num;

    void performCommand_REG(RestaurantTableList &tableList, CustomerPresentStack &presentStack,
                            CustomerWaitingQueue &waitingQueue);

    void performCommand_REGM(RestaurantTableList &tableList, CustomerPresentStack &presentStack);

    void performCommand_CLE(RestaurantTableList &tableList, CustomerPresentStack &presentStack,
                            CustomerWaitingQueue &waitingQueue);

    void performCommand_PS(CustomerPresentStack &presentStack);

    void performCommand_PQ(CustomerWaitingQueue &waitingQueue);

    void performCommand_PT(RestaurantTableList &tableList);

    void performCommand_SQ(CustomerWaitingQueue &waitingQueue);

public:
    Command();
    Command(const Command &c);
    Command(CommandType _type, int _ID, std::string _name, int _age, int _num);
    ~Command();

    Command &operator=(const Command &c);

    void performEncodedOperation(RestaurantTableList &tableList, CustomerPresentStack &presentStack,
                                 CustomerWaitingQueue &waitingQueue);

    void addTokenAsCommandType(const std::string &token);
    void addTokenAsCommandArgument(const std::string &token, int tokenNumber, int tokenCount);
    void addTokenAsCommandDetail(const std::string &token, int tokenNumber, int tokenCount);

    void performSelfcheck();
    bool isValid();

    friend class CommandReader;  // very interesting that this does not required forward declaration
};

#endif
