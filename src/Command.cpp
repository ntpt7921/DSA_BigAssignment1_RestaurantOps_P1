#include "Command.h"
#include "Customer.h"
#include "RestaurantTable.h"

Command::Command() : type(CommandType::INVALID), ID(0), name(), age(0), num(0) { }

Command::Command(const Command &c)
    : type(c.type), ID(c.ID), name(c.name), age(c.age), num(c.num) { }

Command::Command(CommandType _type, int _ID, std::string _name, int _age, int _num)
    : type(_type), ID(_ID), name(_name), age(_age), num(_num)
{
}

Command::~Command() { }

Command &Command::operator=(const Command &c)
{
    this->type = c.type;
    this->ID = c.ID;
    this->name = c.name;
    this->age = c.age;
    this->num = c.num;

    return *this;
}

void Command::performCommand_REG(RestaurantTableList &tableList, CustomerPresentStack &presentStack,
                                 CustomerWaitingQueue &waitingQueue)
{

    RestaurantTable *table = nullptr;
    if (this->ID == 0)
        table = tableList.getFreeSingleTableFromIndex(0);
    else
        table = tableList.getFreeSingleTableFromIndex(this->ID - 1);

    Customer newCustomer({this->ID, (table == nullptr) ? 0 : table->tableID, name, age});

    if (table == nullptr && waitingQueue.currentSize() >= MAXSIZE)
        return;

    // if reach here then total amount of customer is < 2 * MAXSIZE
    if (table == nullptr)
    {
        waitingQueue.enqueue(newCustomer);
    }
    else
    {
        table->customerInfo = newCustomer;
        table->isFree = false;
    }

    presentStack.push(newCustomer);
}

void Command::performCommand_REGM(RestaurantTableList &tableList,
                                  CustomerPresentStack &presentStack)
{
    if (tableList.alreadyHaveGroupTable())
        return;

    RestaurantTable *table = tableList.getFreeGroupTable(this->num);
    if (table == nullptr)
        return;

    Customer newCustomer({0, table->tableID, name, age});
    table->customerInfo = newCustomer;
    table->isFree = false;

    presentStack.push(newCustomer);
}

void Command::performCommand_CLE(RestaurantTableList &tableList, CustomerPresentStack &presentStack,
                                 CustomerWaitingQueue &waitingQueue)
{
    RestaurantTable *cleanAtTable = tableList.cleanTable(this->ID - 1);
    if (cleanAtTable != nullptr)
        presentStack.removeCustomer(cleanAtTable->customerInfo);

    if (waitingQueue.currentSize() > 0)
    {
        Customer nextCustomer = waitingQueue.front();
        waitingQueue.dequeue();

        cleanAtTable->customerInfo = nextCustomer;
        cleanAtTable->isFree = false;
    }
}

void Command::performCommand_PS(CustomerPresentStack &presentStack)
{
    if (num == 0)
        presentStack.printRecentHistory(2 * MAXSIZE);
    else
        presentStack.printRecentHistory(num);
}

void Command::performCommand_PQ(CustomerWaitingQueue &waitingQueue)
{
    if (num == 0)
        waitingQueue.printWaitingCustomer(MAXSIZE);
    else
        waitingQueue.printWaitingCustomer(num);
}

void Command::performCommand_PT(RestaurantTableList &tableList)
{
    tableList.printSeatedTableFromMostRecentlySeated();
}

void Command::performCommand_SQ(CustomerWaitingQueue &waitingQueue)
{
    waitingQueue.prioritizeOldest(num);
}

void Command::performEncodedOperation(RestaurantTableList &tableList,
                                      CustomerPresentStack &presentStack,
                                      CustomerWaitingQueue &waitingQueue)
{
    switch (this->type)
    {
        case CommandType::REG:
            this->performCommand_REG(tableList, presentStack, waitingQueue);
            break;
        case CommandType::REGM:
            this->performCommand_REGM(tableList, presentStack);
            break;
        case CommandType::CLE:
            this->performCommand_CLE(tableList, presentStack, waitingQueue);
            break;
        case CommandType::PS:
            this->performCommand_PS(presentStack);
            break;
        case CommandType::PQ:
            this->performCommand_PQ(waitingQueue);
            break;
        case CommandType::PT:
            this->performCommand_PT(tableList);
            break;
        case CommandType::SQ:
            this->performCommand_SQ(waitingQueue);
            break;
        case CommandType::INVALID:
            break;

        default:
            throw "Oh nyo!!!";
    }
}

void Command::addTokenAsCommandType(const std::string &token)
{
    if (token == "REG")
        this->type = CommandType::REG;
    else if (token == "REGM")
        this->type = CommandType::REGM;
    else if (token == "CLE")
        this->type = CommandType::CLE;
    else if (token == "PS")
        this->type = CommandType::PS;
    else if (token == "PQ")
        this->type = CommandType::PQ;
    else if (token == "PT")
        this->type = CommandType::PT;
    else if (token == "SQ")
        this->type = CommandType::SQ;
    else
        this->type = CommandType::INVALID;
}

void Command::addTokenAsCommandArgument(const std::string &token, int tokenNumber, int tokenCount)
{
    if (tokenNumber < 0)
        return;

    if (tokenNumber >= tokenCount)
        return;

    switch (this->type)
    {
        case CommandType::REG:
            if (tokenCount == 3)
            {
                if (tokenNumber == 1)
                    this->name = token;
                else if (tokenNumber == 2)
                    this->age = std::stoi(token);
                else
                    this->type = CommandType::INVALID;
            }
            else if (tokenCount == 4)
            {
                if (tokenNumber == 1)
                    this->ID = std::stoi(token);
                else if (tokenNumber == 2)
                    this->name = token;
                else if (tokenNumber == 3)
                    this->age = std::stoi(token);
                else
                    this->type = CommandType::INVALID;
            }
            else
                this->type = CommandType::INVALID;
            break;
        case CommandType::REGM:
            if (tokenNumber == 1)
                this->name = token;
            else if (tokenNumber == 2)
                this->age = std::stoi(token);
            else if (tokenNumber == 3)
                this->num = std::stoi(token);
            else
                this->type = CommandType::INVALID;
            break;
        case CommandType::CLE:
            if (tokenNumber == 1)
                this->ID = std::stoi(token);
            else
                this->type = CommandType::INVALID;
            break;
        case CommandType::PS:
            if (tokenNumber == 1)
                this->num = std::stoi(token);
            else
                this->type = CommandType::INVALID;
            break;
        case CommandType::PQ:
            if (tokenNumber == 1)
                this->num = std::stoi(token);
            else
                this->type = CommandType::INVALID;
            break;
        case CommandType::PT:
            this->type = CommandType::INVALID;
            break;
        case CommandType::SQ:
            if (tokenNumber == 1)
                this->num = std::stoi(token);
            else
                this->type = CommandType::INVALID;
            break;
        case CommandType::INVALID:
            break;

        default:
            break;
    }
}

void Command::addTokenAsCommandDetail(const std::string &token, int tokenNumber, int tokenCount)
{
    if (tokenNumber < 0)
        return;

    switch (tokenNumber)
    {
        case 0:
            this->addTokenAsCommandType(token);
            break;

        case 1:
        case 2:
        case 3:
            this->addTokenAsCommandArgument(token, tokenNumber, tokenCount);
            break;

        default:
            break;
    }
}

void Command::performSelfcheck()
{
    if (this->type == CommandType::INVALID)
        return;

    if (this->ID != 0)
        if (this->ID < 1 || this->ID > MAXSIZE)
        {
            this->type = CommandType::INVALID;
            return;
        }

    if (this->age != 0)
        if (this->age < 16 || this->age > 115)
        {
            this->type = CommandType::INVALID;
            return;
        }

    if (this->num != 0)
        if (num <= 0)
        {
            this->type = CommandType::INVALID;
            return;
        }
}

bool Command::isValid() { return (this->type != CommandType::INVALID); }
