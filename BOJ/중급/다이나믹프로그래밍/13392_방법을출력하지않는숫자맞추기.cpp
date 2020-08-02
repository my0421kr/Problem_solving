#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n;
string temp;
vector<int> src, dest;
vector<vector<int>> cache;

void Init()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<10; j++) {
            cache[i][j] = -1;
        }
    }
}

int f(int index, int left)
{
    if(index == n) {
        return 0;
    }
    if(cache[index][left] == -1) {
        int off = ((dest[index] + 10 - src[index])%10 - left + 10)%10;
        int result = 2e9;
        for(int i=0; i<=9; i++) {
            result = min(result, i + (i-off+10)%10 + f(index+1, (i+left)%10));
        }
        cache[index][left] = result;
    }
    return cache[index][left];
}

int main()
{
    scanf("%d", &n);
    cache.assign(n, vector<int>(10, -1));

    cin >> temp;
    int len = (int)temp.size();
    for(int i=0; i<len; i++) {
        src.push_back(temp[i] -'0');
    }
    cin >> temp;
    len = temp.size();
    for(int i=0; i<len; i++) {
        dest.push_back(temp[i] -'0');
    }
    src.push_back(0);
    dest.push_back(0);

    Init();
    printf("%d\n", f(0, 0));
}