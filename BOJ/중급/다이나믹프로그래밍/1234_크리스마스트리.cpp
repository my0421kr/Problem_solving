#include <iostream>
#include <vector>
using namespace std;

int n, m;
long long cache[11][101][101];
vector<vector<long long>> combi;

void Init(int a, int b)
{
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=a; j++) {
            for(int k=0; k<=b; k++) {
                cache[i][j][k] = -1;
            }
        }
    }
}

long long Combi(int num, int k)
{
    if(k == 0 || k == num) {
        return 1;
    } else if(combi[num][k] == -1) {
        combi[num][k] = Combi(num-1, k) + Combi(num-1, k-1);
    }
    return combi[num][k];
}

long long f(int level, int red, int blue, int green)
{
    if(red < 0 || blue < 0 || green < 0) {
        return 0;
    } else if(level == 0) {
        return 1;
    }
    if(cache[level][red][blue] == -1) {
        long long result = 0;
        int temp;
        if(level % 3 == 0) {
            temp = level/3;
            result += f(level-1, red-temp, blue-temp, green-temp) * Combi(level, temp) * Combi(temp*2, temp);
        }
        if(level % 2 == 0) {
            temp = level/2;
            result += f(level-1, red-temp, blue-temp, green) * Combi(level, temp);
            result += f(level-1, red-temp, blue, green-temp) * Combi(level, temp);
            result += f(level-1, red, blue-temp, green-temp) * Combi(level, temp);
        }
        result += f(level-1, red-level, blue, green);
        result += f(level-1, red, blue-level, green);
        result += f(level-1, red, blue, green-level);
        cache[level][red][blue] = result;
    }
    return cache[level][red][blue];
}

int main()
{
    int a, b, c;
    scanf("%d %d %d %d", &n, &a, &b, &c);
    combi.assign(11, vector<long long>(11, -1));

    Init(a, b);
    printf("%lld\n", f(n, a, b, c));
}