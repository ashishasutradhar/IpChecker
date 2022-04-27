# IpChecker
It iterates over newline separated ip addresses in a given file

Configuration:
The input file path can be updated in Common.h file


Compilation:
g++ Utils.cpp IpValidator.cpp FileParser.cpp main.cpp -o ipChecker --std=c++11
