#ifndef COMMANDREADER
#define COMMANDREADER

#include "CircularLinkedList.h"
#include <fstream>
#include <iostream>
#include <string>

class CommandReader
{
private:
    std::ifstream commandFile;

    bool isSpaceChar(char c);
    CircularLinkedList<std::string> * tokenizeLine(const std::string &line);

public:
    CommandReader(std::string _fileName);
    ~CommandReader();

    CircularLinkedList<std::string> * getNextCommandAsTokenList();
    bool canContinueReading();
};

#endif
