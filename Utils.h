#ifndef _UTILS_H_

#include <iostream>
#include <cstdint>
using namespace std;

namespace utils
{
    class IpCounts
    {
        private:
            uint32_t invalidIpCount_;
            uint32_t ipv4Count_;
            uint32_t ipv6Count_;
            uint32_t uniqueIpv4Count_;
            uint32_t ubiqueIpv6Count_;

        public:
        IpCounts();

        const uint32_t& getInvalidIpCount() const{ return invalidIpCount_; }
        void incrementInvalidIpCount(){ ++invalidIpCount_; }
        const uint32_t& getIpv4Count() const{ return ipv4Count_; }
        void incrementIpv4Count() { ++ipv4Count_; }
        const uint32_t& getIpv6Count() const{ return ipv6Count_; }
        void incrementIpv6Count(){ ++ipv6Count_; }
        const uint32_t& getUniqueIpv4Count() const{ return uniqueIpv4Count_; }
        void incrementUniqueIpv4Count(const uint32_t uniqueIpv4Count = 0){ uniqueIpv4Count_+=uniqueIpv4Count; }
        const uint32_t& getUbiqueIpv6Count() const{ return ubiqueIpv6Count_; }
        void incrementUniqueIpv6Count(const uint32_t ubiqueIpv6Count = 0){ ++ubiqueIpv6Count_+=ubiqueIpv6Count; }
        IpCounts operator+(const IpCounts& obj);
    };
};

#endif