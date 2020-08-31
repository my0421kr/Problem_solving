#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

bool IsOk(string str)
{
    bool result = true;
    stack<char> ps;
    for(int i=0; i<str.size(); i++) {
        if(str[i] == '(') {
            ps.push(str[i]);
        } else {
            if(ps.empty()) {
                result = false;
                break;
            } else {
                ps.pop();
            }
        }
    }
    while(!ps.empty()) {
        ps.pop();
    }
    return result;
}

string f(string str)
{
    if(str.compare("") == 0) {
        return "";
    } else {
        string result = "", u = "", v = "";
        int lcnt = 0, rcnt = 0;
        for(int i=0; i<str.size(); i++) {
            if(str[i] == '(') {
                lcnt++;
            } else {
                rcnt++;
            }
            if(lcnt == rcnt) {
                u = str.substr(0, i+1);
                v = str.substr(i+1, str.size()-i-1);
                break;
            }
        }
        if(IsOk(u)) {
            result = u + f(v);
        } else {
            result = "(" + f(v) + ")";
            for(int i=0; i<u.size(); i++) {
                if(u[i] == '(') {
                    u[i] = ')';
                } else {
                    u[i] = '(';
                }
            }
            result += u.substr(1, u.size()-2);
        }
        return result;
    }
}

string solution(string p) {
    string answer = "";

    answer = f(p);

    return answer;
}