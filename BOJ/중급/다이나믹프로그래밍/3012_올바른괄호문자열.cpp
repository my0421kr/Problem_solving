#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> cache;
int n, flag = 0;
char arr[202];

long long Function(int head, int tail)
{
    if(head > tail) {
        return 1;
    }
    if(cache[head][tail] == -1) {
        if(arr[head] == ')' || arr[head] == '}' || arr[head] == ']') {
            cache[head][tail] = 0;
        } else if(arr[tail] == '(' || arr[tail] == '{' || arr[tail] == '[') {
            cache[head][tail] = 0;
        } else {
            long long result = 0;
            for(int i=head+1; i<=tail; i+=2) {
                if(arr[head] == '(') {
                    if(arr[i] == ')' || arr[i] == '?') {
                        result += Function(head+1, i-1) * Function(i+1, tail);
                    }
                } else if(arr[head] == '{') {
                    if(arr[i] == '}' || arr[i] == '?') {
                        result += Function(head+1, i-1) * Function(i+1, tail);
                    }
                } else if(arr[head] == '[') {
                    if(arr[i] == ']' || arr[i] == '?') {
                        result += Function(head+1, i-1) * Function(i+1, tail);
                    }
                } else if(arr[head] == '?') {
                    if(arr[i] == ')' || arr[i] == '}' || arr[i] == ']') {
                        result += Function(head+1, i-1) * Function(i+1, tail);
                    } else if(arr[i] == '?') {
                        result += 3 * Function(head+1, i-1) * Function(i+1, tail);
                    }
                }
                if(result >= 100000) {
                    result = 100000 + result%100000;
                }
            }
            cache[head][tail] = result;
        }
    }
    return cache[head][tail];
}

int main()
{
    scanf("%d", &n);
    cache.assign(n+1, vector<int>(n+1, -1));

    getchar();
    for(int i=1; i<=n; i++) {
        arr[i] = getchar();
    }
    if(n % 2 == 1) {
        printf("0\n");
        return 0;
    }

    long long result = Function(1, n);
    if(result >= 100000) {
        printf("%05lld\n", Function(1, n)%100000);
    } else {
        printf("%lld\n", Function(1, n));
    }
}