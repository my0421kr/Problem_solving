// Not solved
#include <iostream>
#include <vector>
#define MAX 1000000007
using namespace std;

int n, m, p;
int cache[101][101][101];

int Fact(int num)
{
    if(num == 1) {
        return 1;
    } else {
        return Fact(num-1) * num;
    }
}

int f(int numSing, int numSpace, int defi)
{
    printf("%d %d\n", numSing, numSpace);
    if(numSing == numSpace) {
        return Fact(numSing);
    }
    if(cache[numSing][numSpace][defi] == -1) {
        cache[numSing][numSpace][defi] = f(numSing, numSpace-1, defi)*(numSing-m);
    }
    return cache[numSing][numSpace][defi];
}

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

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &m, &p);

    Init();
    printf("%d\n", f(n, p, 0));
}