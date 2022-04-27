#include "Utils.h"
using namespace utils;

IpCounts::IpCounts()
{
    invalidIpCount_  = 0;
    ipv4Count_       = 0;
    ipv6Count_       = 0;
    uniqueIpv4Count_ = 0;
    ubiqueIpv6Count_ = 0;
}

IpCounts IpCounts::operator+(const IpCounts& obj)
{
    IpCounts retObj;
    retObj.invalidIpCount_  = invalidIpCount_  + obj.invalidIpCount_ ; 
    retObj.ipv4Count_       = ipv4Count_       + obj.ipv4Count_      ;
    retObj.ipv6Count_       = ipv6Count_       + obj.ipv6Count_      ;
    retObj.uniqueIpv4Count_ = uniqueIpv4Count_ + obj.uniqueIpv4Count_; 
    retObj.ubiqueIpv6Count_ = ubiqueIpv6Count_ + obj.ubiqueIpv6Count_; 
    return retObj;
}