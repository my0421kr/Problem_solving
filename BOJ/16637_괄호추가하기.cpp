#include <iostream>
#include <algorithm>
using namespace std;

int n, result = -2e9;
char arr[30];

int cal(int num1, int num2, char c)
{
    if(c == '+') return num1 + num2;
    else if(c == '-') return num1 - num2;
    else return num1 * num2;
}

void DFS(int index, int prev)
{
    if(index > n) {
        result = max(result, prev);
        return;
    } else {
        DFS(index+2, cal(prev, arr[index-1]-'0', arr[index-2]));
        DFS(index+4, cal(prev, cal(arr[index-1]-'0', arr[index+1]-'0', arr[index]), arr[index-2]));
    }
}

int main()
{
    scanf("%d", &n);
    scanf("%s", arr);
    arr[n] = '+';
    arr[n+1] = '0';

    DFS(3, arr[0]-'0');
    DFS(5, cal(arr[0]-'0', arr[2]-'0', arr[1]));
    printf("%d\n", result);
}