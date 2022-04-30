#ifndef _IP_VALIDATOR_H_
#include <iostream>
#include <fstream>
#include <limits>
#include <unordered_set>
#include <mutex>
#include "Utils.h"
using namespace utils;
using namespace std;

class IpValidator
{
    private:
    const string filePath_;
    std::ifstream file_;
    streampos memChunk_;
    streampos startPos_;
    streampos endPos_;
    IpCounts counter_;
    mutex &mtx_;
    static unordered_set<string> uniqueIPv4List_;
    static unordered_set<string> uniqueIPv6List_;


    public:
    IpValidator(mutex &mtx,
                const string filePath = "",
                const streampos memChunk = 0,
                const streampos startPos = 0);
    ~IpValidator();
    void operator()();
    void setStartPos(streampos startPos);
    const IpCounts& getCounter(){return counter_;}
    void printCounters();

    private:
    void exploreIps();
    void examineIP(string ip);
    bool isValidIPv6(string ip);
    bool isValidIPv4(string ip);
    bool isInHex(string ip);
};

#endif