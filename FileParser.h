#ifndef _FILE_PARSER_H_

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <thread>
#include <mutex>
#include "IpValidator.h"
#include "Common.h"
using namespace std;

class FileParser
{
    private:
    typedef struct IpValidator_thread_pair
    {
        IpValidator* ipValidator_;
        thread* tInstance_;
    }IpValidator_thread_pair_t;

    private:
    int numThreads_;
    string filePath_;
    std::ifstream file_;
    streampos fileSize_;
    streampos memChunk_;
    vector<IpValidator_thread_pair_t> threadList_;
    IpCounts counter_;
    mutex mtx_;

    private:
    FileParser(int numThreads, string filePath);
    FileParser(const FileParser&) = delete;
    FileParser& operator=(const FileParser&) = delete;
    void joinWorkerThreads();

    public:
    static FileParser& getInstance();
    void createWorkerThreads();
    void printCounters();
    ~FileParser();
};

#endif