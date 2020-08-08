#include <iostream>
using namespace std;

int n;
int cache[10][101][1024];

void Init()
{
    for(int i=0; i<10; i++) {
        for(int j=0; j<=n; j++) {
            for(int k=0; k<1024; k++) {
                cache[i][j][k] = -1;
            }
        }
    }
}

long long f(int index, int path, int count)
{
    if(index < 0 || index > 9) {
        return 0;
    } else if(count == n) {
        if(path == (1<<10)-1) {
            return 1;
        } else {
            return 0;
        }
    }
    if(cache[index][count][path] == -1) {
        long long result = 0;
        result += f(index+1, path|(1<<(index+1)), count+1);
        result += f(index-1, path|(1<<(index-1)), count+1);
        result %= (long long)1e9;
        cache[index][count][path] = result;
    }
    return cache[index][count][path];
}

int main()
{
    scanf("%d", &n);
    Init();

    long long answer = 0;
    for(int i=1; i<10; i++) {
        answer += f(i, 1<<i, 1);
        answer %= (long long)1e9;
    }
    printf("%lld\n", answer);
}