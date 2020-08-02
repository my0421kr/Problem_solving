#include <iostream>
#include <vector>
#define MOD 1000001
using namespace std;

int n, m, k;
long long cache[101][101][101];

void Init()
{
    for(int i=0; i<=100; i++) {
        for(int j=0; j<=100; j++) {
            for(int k=0; k<=100; k++) {
                cache[i][j][k] = -1;
            }
        }
    }
}

long long f(int row, int col, int remain)
{
    if(row < 0 || col < 0 || remain < 0) {
        return 0;
    } else if(remain == 0) {
        return 1;
    }
    if(cache[row][col][remain] == -1) {
        long long result = 0;
        result += f(row-1, col, remain);
        result += f(row-1, col-1, remain-1)*col;
        result += f(row-1, col-2, remain-2)*((col*(col-1))/2);
        result += f(row-2, col-1, remain-2)*(row-1)*col;
        cache[row][col][remain] = result%MOD;
    }
    return cache[row][col][remain];
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);

    Init();
    printf("%lld\n", f(n, m, k));
}