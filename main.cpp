#include <iostream>
#include <chrono>
#include "FileParser.h"
using namespace std;
using namespace std::chrono;

int main()
{
    milliseconds start_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    FileParser::getInstance().createWorkerThreads();
    FileParser::getInstance().printCounters();
    milliseconds end_ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout<<"Time taken to compute in ms: "<<(end_ms-start_ms).count()<<endl;
}