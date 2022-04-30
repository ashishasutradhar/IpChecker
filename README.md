# IpChecker<br />
It iterates over newline separated ip addresses in a given file<br />
<br />

Configuration:<br />
The input file path can be updated in Common.h file<br />
<br />

Compilation:<br />
g++ Utils.cpp IpValidator.cpp FileParser.cpp main.cpp -o ipChecker --std=c++11<br />
<br />

Execution:<br />
./ipChecker<br />
<br />

Sample Output:
<pre>
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
</pre>
