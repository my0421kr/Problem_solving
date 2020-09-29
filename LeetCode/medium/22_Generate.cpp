#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    void f(int left, int right, int n, string &result, vector<string> &answer) {
        if(left == n && right == n) {
            answer.push_back(result);
            return;
        }
        if(left > n || right > n) {
            return;
        }
        result.push_back('(');
        f(left+1, right, n, result, answer);
        result.pop_back();
        if(left > right) {
            result.push_back(')');
            f(left, right+1, n, result, answer);
            result.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        string result;
        vector<string> answer(0);
        f(0, 0, n, result, answer);
        return answer;
    }
};