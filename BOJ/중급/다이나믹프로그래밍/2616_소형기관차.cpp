#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, max_cnt;
int arr[50001], arr_sum[50001];
int cache[4][50001];

void Init()
{
    for(int i=0; i<=3; i++) {
        for(int j=0; j<=n; j++) {
            cache[i][j] = -1;
        }
    }
}

void Make_Sum()
{
    arr_sum[1] = arr[1];
    for(int i=1; i<=n; i++) {
        arr_sum[i] = arr_sum[i-1] + arr[i];
    }
}

int Partial_Sum(int head, int tail)
{
    return arr_sum[tail] - arr_sum[head-1];
}

int f(int count, int index)
{
    if(index <= 0 || count == 0) {
        return 0;
    } else if(cache[count][index] == -1) {
        cache[count][index] = max(f(count, index-1), f(count-1, index-max_cnt) + Partial_Sum(index-max_cnt+1, index));
    }
    return cache[count][index];
}

int main()
{
    scanf("%d", &n);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &max_cnt);

    Init();
    Make_Sum();
    printf("%d\n", f(3, n));
}