#include <iostream>
#include <vector>
#define MAX 1000000007
using namespace std;

int n, m, p;
vector<vector<long long>> cache;

long long f(int inserted, int space)
{
    if(inserted == 0 && space == 0) {
        return 1;
    } else if(inserted == 0 || space == 0) {
        return 0;
    }
    if(cache[inserted][space] == -1) {
        cache[inserted][space] = f(inserted-1, space-1) * (n - (inserted - 1));
        if(inserted >= m) {
            cache[inserted][space] += f(inserted, space-1) * (inserted - m);
        }
        cache[inserted][space] %= MAX;
    }
    return cache[inserted][space];
}

int main()
{
    scanf("%d %d %d", &n, &m, &p);

    cache.assign(n+1, vector<long long>(p+1, -1));
    printf("%lld\n", f(n, p));
}