#ifndef COMMANDREADER
#define COMMANDREADER

#include "CircularLinkedList.h"
#include "Command.h"
#include <fstream>
#include <iostream>
#include <string>

class CommandReader
{
private:
    std::ifstream commandFile;

    bool isSpaceChar(char c);
    CircularLinkedList<std::string> *tokenizeLine(const std::string &line);
    CircularLinkedList<std::string> *getNextCommandAsTokenList();

public:
    CommandReader(std::string _fileName);
    ~CommandReader();

    Command readNextCommand();

    bool canContinueReading();
};

#endif
