#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a, b;
long long x, y;
int infoLine[501];
long long cache[101][501][3];

void Init()
{
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=m; j++) {
            cache[i][j][0] = -1;
            cache[i][j][1] = -1;
            cache[i][j][2] = -1;
        }
    }
}

long long f(int cur, int level, int flag)
{
    if(cur <= 0 || cur > n) {
        return 2e9;
    }
    if(level == -1) {
        if(cur == a) {
            return 0;
        } else {
            return 2e9;
        }
    }
    if(cache[cur][level][flag] == -1) {
        long long result = 2e9;
        if(flag == 0) {
            if(infoLine[level] == cur || infoLine[level] == cur-1) {
                result = min(result, f(cur, level-1, 0) + x);
                result = min(result, f(cur, level-1, 1) + x);
                result = min(result, f(cur, level-1, 2) + x);
            } else {
                result = min(result, f(cur, level-1, 0));
                result = min(result, f(cur, level-1, 1));
                result = min(result, f(cur, level-1, 2));
            }
        } else if(flag == 1) {
            if(infoLine[level] == cur) {
                result = min(result, f(cur-1, level, 0) + y);
                result = min(result, f(cur-1, level, 1) + y);
            } else if(infoLine[level] == cur-1) {
                result = min(result, f(cur-1, level-1, 0));
                result = min(result, f(cur-1, level-1, 1));
                result = min(result, f(cur-1, level-1, 2));
            } else {
                result = min(result, f(cur-1, level, 0) + y);
                result = min(result, f(cur-1, level, 1) + y);
            }
        } else {
            if(infoLine[level] == cur) {
                result = min(result, f(cur+1, level-1, 0));
                result = min(result, f(cur+1, level-1, 1));
                result = min(result, f(cur+1, level-1, 2));
            } else if(infoLine[level] == cur-1) {
                result = min(result, f(cur+1, level, 0) + y);
                result = min(result, f(cur+1, level, 2) + y);
            } else {
                result = min(result, f(cur+1, level, 0) + y);
                result = min(result, f(cur+1, level, 2) + y);
            }
        }
        cache[cur][level][flag] = result;
    }
    return cache[cur][level][flag];
}

int main()
{
    scanf("%d %d %d %d %lld %lld", &n, &m, &a, &b, &x, &y);

    infoLine[0] = -100;
    for(int i=1; i<=m; i++) {
        scanf("%d", &infoLine[i]);
    }

    Init();
    long long answer = 2e18;
    for(int i=0; i<3; i++) {
        answer = min(answer, f(b, m, i));
    }
    printf("%lld\n", answer);
}