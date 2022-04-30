# IpChecker
It iterates over newline separated ip addresses in a given file

Configuration:
The input file path can be updated in Common.h file


Compilation:
g++ Utils.cpp IpValidator.cpp FileParser.cpp main.cpp -o ipChecker --std=c++11


Execution:
./ipChecker


Sample Output:
FileParser Created.
File ./sampleInput.txt opened.
File size: 12006915
Total IPs processed       : 1000000
Total IPv4 address count  : 741071
Total IPv6 address count  : 10
Unique IPv4 address count : 353
Unique IPv6 address count : 9
Invalid IP address count  : 258919
Time taken to compute in ms: 2488