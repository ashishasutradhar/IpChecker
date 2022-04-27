#include <iostream>
#include "FileParser.h"
using namespace std;

int main()
{
    FileParser::getInstance().createWorkerThreads();
    FileParser::getInstance().printCounters();
}