#include "IpValidator.h"
#include <vector>
#include <sstream>

unordered_set<string> IpValidator::uniqueIPv4List_;
unordered_set<string> IpValidator::uniqueIPv6List_;

IpValidator::IpValidator(mutex &mtx, const string filePath, const streampos memChunk, const streampos startPos): filePath_(filePath), startPos_(startPos), memChunk_(memChunk), mtx_(mtx)
{
    file_.open(filePath_, ios_base::binary); //need to handle exception
    file_.seekg(startPos); //updating the read pointer
    endPos_ = startPos_ + memChunk_;
}

IpValidator::~IpValidator()
{
    file_.close();
}

void IpValidator::operator()()
{
    exploreIps();
}

void IpValidator::setStartPos(const streampos startPos)
{
    startPos_ = startPos;
    file_.seekg(startPos_); //updating the read pointer
    endPos_ = startPos_ + memChunk_;
}

void IpValidator::exploreIps()
{
    string ip;
    uniqueIPv4List_.clear();
    uniqueIPv6List_.clear();
    while(file_ and file_.tellg() < endPos_)
    {
        getline(file_, ip);
        examineIP(ip);
        file_.tellg();
    }
    //printCounters();
}

void IpValidator::examineIP(string ip)
{
    if (isValidIPv4(ip))
    {
        counter_.incrementIpv4Count();
        if(uniqueIPv4List_.find(ip) == uniqueIPv4List_.end())
        {
            {
                lock_guard<mutex> lock(mtx_);
                //cout<<"unique IP: "<<ip<<endl;//debug log
                uniqueIPv4List_.insert(ip);
            }
            counter_.incrementUniqueIpv4Count();
        }
    }
    else if (isValidIPv6(ip))
    {
        counter_.incrementIpv6Count();
        if(uniqueIPv6List_.find(ip) == uniqueIPv6List_.end())
        {
            {
                lock_guard<mutex> lock(mtx_);
                uniqueIPv6List_.insert(ip);
            }
            counter_.incrementUniqueIpv6Count();
        }
    }
    else
    {
        counter_.incrementInvalidIpCount();
    }
}

bool IpValidator::isValidIPv4(string ip)
{
    int count = 0;

    // counting "."
    for (int i = 0; i < ip.size(); i++) {
        if (ip[i] == '.')
            count++;
    }

    if (count != 3)
        return false;

    vector<string> tokens;

    stringstream check1(ip);
    string intermediate;

    // Tokenizing w.r.t. '.'
    while (getline(check1,
                intermediate, '.')) {
        tokens.push_back(intermediate);
    }

    if (tokens.size() != 4)
        return false;

    for (int i = 0; i < tokens.size(); i++) {
        int num = 0;

        // Base Case
        if (tokens[i] == "0")
            continue;

        if (tokens[i].size() == 0)
            return false;

        for (int j = 0;
            j < tokens[i].size();
            j++) {
            if (tokens[i][j] > '9'
                || tokens[i][j] < '0')
                return false;

            num *= 10;
            num += tokens[i][j] - '0';

            if (num == 0)
                return false;
        }
        if (num > 255 || num < 0)
            return false;
    }

    return true;
}

bool IpValidator::isInHex(string ip)
{
    int n = ip.length();

    for (int i = 0; i < n; i++) {
        char ch = ip[i];

        // Check for valid char
        if ((ch < '0' || ch > '9')
            && (ch < 'A' || ch > 'F')
            && (ch < 'a' || ch > 'f')) {
            return false;
        }
    }

    return true;
}

bool IpValidator::isValidIPv6(string ip)
{
    int count = 0;
    //counting ":"
    for (int i = 0; i < ip.size();
        i++) {
        if (ip[i] == ':')
            count++;
    }

    if (count != 7)
        return false;

    vector<string> tokens;

    stringstream check1(ip);
    string intermediate;

    // Tokenizing w.r.t. ':'
    while (getline(
        check1,
        intermediate, ':')) {
        tokens.push_back(intermediate);
    }

    if (tokens.size() != 8)
        return false;

    // Check if all tokens are in hex
    for (int i = 0;
        i < tokens.size(); i++) {

        int len = tokens[i].size();

        if (!isInHex(tokens[i])
            || len > 4 || len < 1) {
            return false;
        }
    }
    return true;
}

void IpValidator::printCounters()
{
    cout<<"Total IPv4 address count  : "<<counter_.getIpv4Count()<<endl;
    cout<<"Total IPv6 address count  : "<<counter_.getIpv6Count()<<endl;
    cout<<"Unique IPv4 address count : "<<counter_.getUniqueIpv4Count()<<endl;
    cout<<"Unique IPv6 address count : "<<counter_.getUbiqueIpv6Count()<<endl;
    cout<<"Invalid IP address count  : "<<counter_.getInvalidIpCount()<<endl;
}