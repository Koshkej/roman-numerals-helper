#include <iostream>
#include <map>
#include <string>
#include <math.h>

class RomanHelper {
private:

    std::map<std::string, int> numlit = { 
        {"N", 0},
        {"I", 1},
        {"V", 5},
        {"X", 10},
        {"L", 50},
        {"C", 100},
        {"D", 500},
        {"M", 1000},
    };

    std::map<int, std::string> litnum = {
        {1, "I"},
        {5, "V"},
        {10, "X"},
        {50, "L"},
        {100, "C"},
        {500, "D"},
        {1000, "M"},
    };

public:
    std::string to_roman(unsigned int n) {
        int burresult[4] = { 
            n / 1000, 
            (n - ((n / 1000) * 1000)) / 100, 
            (n - ((n / 1000) * 1000) - (((n - ((n / 1000) * 1000)) / 100) * 100)) / 10,
            n % 10 
        };       
        std::string result;
        
        for (int i = 0; i < 4; i++) {
            if (burresult[i] == 0) continue;
            if (burresult[i] < 4) {
                for (int y = 0; y < burresult[i]; y++) {
                    result += litnum[std::pow(10, 3 - i)];
                }
            }
            if (burresult[i] == 4) {
                result += (litnum[std::pow(10, 3 - i)] + litnum[std::pow(10, 3 - i) * 5]);
            }
            if (burresult[i] == 5) {
                result += litnum[std::pow(10, 3 - i) * 5];
            }
            if (burresult[i] > 5 and burresult[i] < 9) {
                result += litnum[std::pow(10, 3 - i) * 5];
                for (int y = 0; y < burresult[i] - 5; y++) {
                    result += litnum[std::pow(10, 3 - i)];
                }
            }
            if (burresult[i] == 9) {
                result += (litnum[std::pow(10, 3 - i)] + litnum[std::pow(10, 3 - i + 1)]);
            }
        }

        return result;
    }
    int from_roman(std::string rn) {
        rn += "N";
        int burresult[4] = { 0,0,0,0 };
        int result = 0;
        int demention = 0;

        for (int i = 0; i < rn.size() - 1; i++) {
            std::string bufsrt1, bufsrt2;
            bufsrt1 += rn[i];
            bufsrt2 += rn[i + 1];
            if (numlit[bufsrt1] == numlit[bufsrt2]) {
                burresult[demention] += numlit[bufsrt1];
            }
            if (numlit[bufsrt1] < numlit[bufsrt2]) {
                burresult[demention] += (numlit[bufsrt2] - numlit[bufsrt1]);
                i++;
            }
            if (numlit[bufsrt1] > numlit[bufsrt2]) {
                if ( (numlit[bufsrt1] + numlit[bufsrt2]) % int(std::pow(10, 3 - demention)) == 0){
                    burresult[demention] += numlit[bufsrt1] + numlit[bufsrt2];
                    i++;
                }
                else {
                    burresult[demention] += numlit[bufsrt1];
                    demention++;
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            result += burresult[i];
        }
        return result;
    }
};

int main()
{
    RomanHelper test;
    std::cout << test.from_roman("MDCLXVI");
    return 0;
}