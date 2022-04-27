#include "IpValidator.h"
#include <vector>
#include <sstream>

IpValidator::IpValidator(const string filePath, const streampos memChunk, const streampos startPos): filePath_(filePath), startPos_(startPos), memChunk_(memChunk)
{
    cout<<"IpValidator::creating IpValidator Instance"<<endl; //debug log
    file_.open(filePath_, ios_base::binary); //need to handle exception
    file_.seekg(startPos); //updating the read pointer
    endPos_ = file_.tellg() + memChunk_;
}

IpValidator::~IpValidator()
{
    cout<<"IpValidator::~IpValidator Closing file"<<endl; //debug log
    file_.close();
}

void IpValidator::operator()()
{
    cout<<"Worker Thread Created"<<endl; //debug log
    exploreIps();
}

void IpValidator::setStartPos(const streampos startPos)
{
    startPos_ = startPos;
    file_.seekg(startPos); //updating the read pointer
    endPos_ = file_.tellg() + memChunk_;
    cout<<"IpValidator::setting startPos: "<<startPos_<<" and endPos: "<<endPos_<<endl;//debug log
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
    }
    counter_.incrementUniqueIpv4Count(uniqueIPv4List_.size());
    counter_.incrementUniqueIpv6Count(uniqueIPv6List_.size());
    printCounters();
}

void IpValidator::examineIP(string ip)
{
    cout<<"IP: "<<ip<<endl;//debug log
    if (isValidIPv4(ip))
    {
        cout<<"IPv4"<<endl;//debug log
        counter_.incrementIpv4Count();
        uniqueIPv4List_.insert(ip);
    }
    else if (isValidIPv6(ip))
    {
        cout<<"IPv6"<<endl;//debug log
        counter_.incrementIpv6Count();
        uniqueIPv6List_.insert(ip);
    }
    else
    {
        cout<<"Invalid IP"<<endl;//debug log
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