#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int g(int start, int toksize, string &temp, string &str)
{
    int result = 0;
    for(int i=start; i<=str.size()-toksize; i+=toksize) {
        if(temp.compare(str.substr(i, toksize)) == 0) {
            result++;
        } else {
            break;
        }
    }
    return result;
}

int f(int toksize, string &str)
{
    int result = str.size(), count, i, j;
    for(i=0; i<str.size()-toksize; i+=toksize) {
        string temp = str.substr(i, toksize);
        count = g(i+toksize, toksize, temp, str);
        if(count != 0) {
            result -= count*toksize;
            if(count < 9) {
                result++;
            } else if(count < 99) {
                result+=2;
            } else if(count < 999) {
                result+=3;
            } else {
                result+=4;
            }
        }
        i+=toksize*count;
    }
    return result;
}

int solution(string s) {
    int answer = s.size();
    for(int i=1; i<=s.size()/2; i++) {
        answer = min(answer, f(i, s));
    }
    return answer;
}