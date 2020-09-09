#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string s;
vector<vector<int>> cache, dp;

int IsPal(int head, int tail)
{
    if(cache[head][tail] == -1) {
        if(head > tail) {
            cache[head][tail] = 1;
        } else if(head == tail) {
            cache[head][tail] = 1;
        } else if(s[head] == s[tail]) {
            cache[head][tail] = IsPal(head+1, tail-1);
        } else {
            cache[head][tail] = 0;
        }
    }
    return cache[head][tail];
}

int f(int head, int tail)
{
    if(head > tail) {
        return 0;
    } else if(dp[head][tail] == -1) {
        int result = 2e9;
        for(int i=head; i<=tail; i++) {
            if(IsPal(head, i)) {
                result = min(result, f(i+1, tail) + 1);
            }
        }
        dp[head][tail] = result;
    }
    return dp[head][tail];
}

int main()
{
    cin >> s;
    cache.assign(s.size(), vector<int>(s.size(), -1));
    dp.assign(s.size(), vector<int>(s.size(), -1));

    int answer = 2e9;
    for(int i=0; i<s.size(); i++) {
        if(IsPal(0, i)) {
            answer = min(answer, f(i+1, s.size()-1)+1);
        }
    }
    printf("%d\n", answer);
}