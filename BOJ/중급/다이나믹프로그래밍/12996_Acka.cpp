#include <iostream>
using namespace std;

int n, na, nb, nc;
long long cache[51][51][51][51];

void Init()
{
    int i, j, k, p;
    for(i=0; i<=n; i++) {
        for(j=0; j<=na; j++) {
            for(k=0; k<=nb; k++) {
                for(p=0; p<=nc; p++) {
                    cache[i][j][k][p] = -1;
                }
            }
        }
    }
}

long long f(int rn, int ra, int rb, int rc)
{
    if(rn == 0 && ra == 0 && rb == 0 && rc == 0) {
        return 1;
    } else if(rn < 0 || ra < 0 || rb < 0 || rc < 0) {
        return 0;
    } else if(cache[rn][ra][rb][rc] == -1) {
        cache[rn][ra][rb][rc] = 0;
        cache[rn][ra][rb][rc] += f(rn-1, ra, rb, rc-1);
        cache[rn][ra][rb][rc] += f(rn-1, ra, rb-1, rc);
        cache[rn][ra][rb][rc] += f(rn-1, ra, rb-1, rc-1);
        cache[rn][ra][rb][rc] += f(rn-1, ra-1, rb, rc);
        cache[rn][ra][rb][rc] += f(rn-1, ra-1, rb, rc-1);
        cache[rn][ra][rb][rc] += f(rn-1, ra-1, rb-1, rc);
        cache[rn][ra][rb][rc] += f(rn-1, ra-1, rb-1, rc-1);
        cache[rn][ra][rb][rc] %= (long long)(1e9 + 7);
    }
    return cache[rn][ra][rb][rc];
}

int main()
{
    scanf("%d %d %d %d", &n, &na, &nb, &nc);

    Init();
    printf("%lld\n", f(n, na, nb, nc));
}