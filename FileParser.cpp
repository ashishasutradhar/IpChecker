#include "FileParser.h"
#include <thread>

FileParser::FileParser(int numThreads, string filePath): numThreads_(numThreads), filePath_(filePath)
{
    cout<<"FileParser Created."<<endl;
    file_.open(filePath_, ios_base::binary); //need to handle exception
    cout<<"File "<<filePath<<" opened."<<endl;
    file_.seekg(0, file_.end);
    fileSize_ = file_.tellg();
    file_.seekg(0, file_.beg);
    cout<<"File size: "<<fileSize_<<endl;
    memChunk_ = fileSize_/numThreads_;
    for(int i=0; i<numThreads; i++)
    {
        IpValidator_thread_pair_t ipValidatorThreadPair;
        ipValidatorThreadPair.ipValidator_ = new IpValidator(mtx_, filePath_,memChunk_);
        ipValidatorThreadPair.tInstance_ = nullptr;
        threadList_.push_back(ipValidatorThreadPair);
    }
}

FileParser::~FileParser()
{
    file_.close();
}

FileParser& FileParser::getInstance()
{
    static FileParser fileParser(NUM_OF_THREADS, FILE_PATH);
    return fileParser;
}

void FileParser::createWorkerThreads()
{
    int i = 0;
    while(file_)
    {
        //1. create thread
        threadList_[i].ipValidator_->setStartPos(file_.tellg());
        threadList_[i].tInstance_ = new thread(ref(*(threadList_[i].ipValidator_)));
        //2. increment seek counter
        file_.seekg(memChunk_, ios_base::cur);
        //3. increment till the next line
        string str;
        getline(file_, str);
        i++;
    }
    joinWorkerThreads();
}

void FileParser::joinWorkerThreads()
{
    for(int i=0; i<numThreads_; ++i)
    {
        if(threadList_[i].tInstance_)
        {
            if(threadList_[i].tInstance_->joinable())
            {
                threadList_[i].tInstance_->join();
            }
            counter_ = counter_ + threadList_[i].ipValidator_->getCounter();
        }
        delete threadList_[i].ipValidator_;
        delete threadList_[i].tInstance_;
    }
}

void FileParser::printCounters()
{
    cout<<"Total IPs processed       : "<<(counter_.getIpv4Count()+
                                          counter_.getIpv6Count() +
                                          counter_.getInvalidIpCount())<<endl;
    cout<<"Total IPv4 address count  : "<<counter_.getIpv4Count()<<endl;
    cout<<"Total IPv6 address count  : "<<counter_.getIpv6Count()<<endl;
    cout<<"Unique IPv4 address count : "<<counter_.getUniqueIpv4Count()<<endl;
    cout<<"Unique IPv6 address count : "<<counter_.getUbiqueIpv6Count()<<endl;
    cout<<"Invalid IP address count  : "<<counter_.getInvalidIpCount()<<endl;
}