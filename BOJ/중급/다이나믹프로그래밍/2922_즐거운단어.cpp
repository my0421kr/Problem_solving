#include <iostream>
#include <string.h>
using namespace std;

char arr[102];
long long cache[101][101][2][2][2];
int n;

int IsWhat(char c)
{
    if(c == '_') {
        return 2;
    } else if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return 0;
    } else {
        return 1;
    }
}

void Init()
{
    for(int i=2; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            for(int k=0; k<2; k++) {
                for(int p=0; p<2; p++) {
                    for(int q=0; q<2; q++) {
                        cache[i][j][k][p][q] = -1;
                    }
                }
            }
        }
    }
}

long long f(int index, int l, int prev2, int prev, int cur)
{
    if( (prev2 == 0 && prev == 0 && cur == 0) || (prev2 == 1 && prev == 1 && cur == 1) ){
        return 0;
    }
    if(cache[index][l][prev2][prev][cur] == -1) {
        long long result = 0;
        int flag = IsWhat(arr[index]);
        if(flag == 0) {
            if(cur == 0) {
                result += f(index-1, l, 0, prev2, prev);
                result += f(index-1, l, 1, prev2, prev);
            }
        } else if(flag == 1) {
            if(cur == 1) {
                if(arr[index] == 'L') {
                    result += f(index-1, l-1, 0, prev2, prev);
                    result += f(index-1, l-1, 1, prev2, prev);
                } else {
                    result += f(index-1, l, 0, prev2, prev);
                    result += f(index-1, l, 1, prev2, prev);
                }
            }
        } else {
            if(cur == 0) {
                result += f(index-1, l, 0, prev2, prev) * 5;
                result += f(index-1, l, 1, prev2, prev) * 5;
            } else {
                result += f(index-1, l, 0, prev2, prev) * 20;
                result += f(index-1, l, 1, prev2, prev) * 20;
                result += f(index-1, l-1, 0, prev2, prev);
                result += f(index-1, l-1, 1, prev2, prev);
            }
        }
        cache[index][l][prev2][prev][cur] = result;
    }
    return cache[index][l][prev2][prev][cur];
}

int main()
{
    scanf("%s", arr+1);
    n = (int)strlen(arr+1);
    Init();

    int flag = IsWhat(arr[1]);
    if(flag == 0) {
        cache[1][0][0][1][0] = 1;
    } else if(flag == 1) {
        if(arr[1] == 'L') {
            cache[1][1][0][0][1] = 1;
        } else {
            cache[1][0][0][0][1] = 1;
        }
    } else {
        cache[1][0][0][1][0] = 5;
        cache[1][0][0][0][1] = 20;
        cache[1][1][0][0][1] = 1;
    }

    long long answer = 0;
    for(int i=1; i<=n; i++) {
        answer += f(n, i, 0, 0, 1);
        answer += f(n, i, 0, 1, 0);
        answer += f(n, i, 0, 1, 1);
        answer += f(n, i, 1, 0, 0);
        answer += f(n, i, 1, 0, 1);
        answer += f(n, i, 1, 1, 0);
    }
    printf("%lld\n", answer);

}