#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> arr1, arr2;
map<string, int> pm1, pm2, visit1, visit2;

bool IsAlpha(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool IsCap(char c)
{
    return ('A' <= c && c <= 'Z');
}

void Parsing(string &str, vector<string> &arr)
{
    for(int i=0; i<str.size()-1; i++) {
        string temp = str.substr(i, 2);
        if(IsAlpha(temp[0]) && IsAlpha(temp[1])) {
            if(IsCap(temp[0])) {
                temp[0] -= 'A' - 'a';
            }
            if(IsCap(temp[1])) {
                temp[1] -= 'A' - 'a';
            }
            arr.push_back(temp);
        }
    }
}

int solution(string str1, string str2) {
    int answer = 0;
    Parsing(str1, arr1);
    Parsing(str2, arr2);

    int inter = 0, uni = 0;
    for(int i=0; i<arr1.size(); i++) {
        pm1[arr1[i]]++;
    }
    for(int i=0; i<arr2.size(); i++) {
        pm2[arr2[i]]++;
    }

    for(int i=0; i<arr1.size(); i++) {
        if(visit1[arr1[i]] == 0) {
            uni += max(pm1[arr1[i]], pm2[arr1[i]]);
            visit1[arr1[i]] = 1;
        }
    }
    for(int i=0; i<arr2.size(); i++) {
        if(visit1[arr2[i]] == 0) {
            uni += max(pm1[arr2[i]], pm2[arr2[i]]);
            visit1[arr2[i]] = 1;
        }
    }

    for(int i=0; i<arr1.size(); i++) {
        if(visit2[arr1[i]] == 0) {
            inter += min(pm1[arr1[i]], pm2[arr1[i]]);
            visit2[arr1[i]] = 1;
        }
    }
    if(arr1.size() == 0 && arr2.size() == 0) {
        return 65536;
    }

    inter *= 65536;
    answer = inter/uni;

    return answer;
}