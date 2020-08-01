#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int t, n, m;
char cache[5001][5001];
vector<int> arr;

void Init()
{
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            cache[i][j] = -1;
        }
    }
}

int f(int whole, int score)
{
    if(whole == 0 && score == 0) {
        return 1;
    } else if (whole < 0 || score < 0) {
        return 0;
    }
    if(cache[whole][score] == -1) {
        int result = 0;
        int temp = whole - score;
        for(int i=0; i<m; i++) {
            if(f(temp, score - arr[i]) == 1) {
                result = 1;
                break;
            }
        }
        cache[whole][score] = result;
    }
    return cache[whole][score];
}

int main()
{
    scanf("%d", &t);

    int i, j;
    for(i=0; i<t; i++) {
        scanf("%d %d", &n, &m);
        arr.clear();
        arr.resize(m);
        Init();
        for(j=0; j<m; j++) {
            scanf("%d", &arr[j]);
        }

        for(j=n; j>0; j--) {
            if(f(n, j) == 1) {
                printf("%d\n", j);
                break;
            }
        }

        if(j == 0) {
            printf("-1\n");
        }
    }
}