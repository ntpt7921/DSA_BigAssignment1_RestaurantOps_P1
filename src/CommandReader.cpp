#include "CommandReader.h"

bool CommandReader::isSpaceChar(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\n':
        case '\v':
        case '\f':
        case '\r':
            return true;
        default:
            return false;
    }

    return false;
}

CircularLinkedList<std::string> * CommandReader::tokenizeLine(const std::string &line)
{
    static const std::string spaceCharList = " \t\n\v\f\r";

    CircularLinkedList<std::string> *result = new CircularLinkedList<std::string>();
    bool expectSpaceTokenNext = this->isSpaceChar(line[0]);

    if (line.empty())
        return result;

    std::string::size_type start = 0, end = std::string::npos;
    while (true)
    {
        if (expectSpaceTokenNext)
        {
            end = line.find_first_not_of(spaceCharList, start);
            // don't output space as token, so no format testing
            // result->insertAtEnd(line.substr(start, end));
        }
        else
        {
            end = line.find_first_of(spaceCharList, start);
            result->insertAtEnd(line.substr(start, end));
        }

        if (end == std::string::npos)
            break;
        expectSpaceTokenNext = !expectSpaceTokenNext;
        start = end;
    }
    return result;
}

CircularLinkedList<std::string> * CommandReader::getNextCommandAsTokenList()
{
    std::string line;
    if (this->canContinueReading())
        std::getline(commandFile, line);

    return tokenizeLine(line);
}

CommandReader::CommandReader(std::string _fileName):
    commandFile(_fileName, std::ios::in)
{
    if (!commandFile.is_open())
        throw "CommandReader::constructor(std::string) - "
              "Fail to open file with provided name";
}

CommandReader::~CommandReader()
{
    commandFile.close();
}

bool CommandReader::canContinueReading()
{
    return (!commandFile); // no EOF or error has happened
}
