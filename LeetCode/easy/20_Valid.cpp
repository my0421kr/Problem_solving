#include <string>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> ps;
        for(int i=0; i<s.size(); i++) {
            if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
                ps.push(s[i]);
            } else {
                char c;
                if(ps.empty()) {
                    return false;
                } else {
                    c = ps.top();
                    ps.pop();
                }
                if(s[i] == ')' && c == '(') {
                    continue;
                } else if(s[i] == '}' && c == '{') {
                    continue;
                } else if(s[i] == ']' && c == '[') {
                    continue;
                } else {
                    return false;
                }
            }
        }
        return ps.empty() ? true : false;
    }
};