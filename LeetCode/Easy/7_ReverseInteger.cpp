#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        string str = to_string(abs(x));
        std::reverse(str.begin(), str.end());
        string answer = "";
        if(x >= 0) {
            answer = str;
        } else {
            answer = '-' + str;
        }

        long long temp = stoll(answer);
        if(temp > INT32_MAX || temp < INT32_MIN) {
            return 0;
        } else {
            return temp;
        }
    }
};