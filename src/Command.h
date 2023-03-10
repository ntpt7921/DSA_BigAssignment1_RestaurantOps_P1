#ifndef COMMAND
#define COMMAND

#include <string>

class Command
{
private:
    enum class CommandType
    {
        REG,
        REGM,
        CLE,
        PS,
        PQ,
        PT,
        SQ,
    };

    CommandType type;
    int ID;
    std::string name;
    int age;
    int num;
};

#endif
