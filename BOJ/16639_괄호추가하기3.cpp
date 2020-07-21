#include <iostream>
#include <algorithm>
using namespace std;

int n, len, answer = -2e9;
char arr[40];
int f(int head, int tail);
int g(int head, int tail);

int f(int head, int tail)
{
    int result = -2e9;
    if(head == tail) {
        return arr[head] - '0';
    } else {
        for(int i=head+1; i<tail; i+=2) {
            if(arr[i] == '+') {
                result = max(result, f(head, i-1) + f(i+1, tail));
            } else if(arr[i] == '-') {
                result = max(result, f(head, i-1) - g(i+1, tail));
            } else {
                result = max(result, f(head, i-1) * f(i+1, tail));
                result = max(result, g(head, i-1) * g(i+1, tail));
            }
        }
        return result;
    }
}

int g(int head, int tail)
{
    int result = 2e9;
    if(head == tail) {
        return arr[head] - '0';
    } else {
        for(int i=head+1; i<tail; i+=2) {
            if(arr[i] == '+') {
                result = min(result, g(head, i-1) + g(i+1, tail));
            } else if(arr[i] == '-') {
                result = min(result, g(head, i-1) - f(i+1, tail));
            } else {
                result = min(result, f(head, i-1) * f(i+1, tail));
                result = min(result, g(head, i-1) * g(i+1, tail));
                result = min(result, f(head, i-1) * g(i+1, tail));
                result = min(result, g(head, i-1) * f(i+1, tail));
            }
        }
        return result;
    }
}

int main()
{
    scanf("%d", &n);
    scanf("%s", arr);

    printf("%d\n", f(0, n-1));
}