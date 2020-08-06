#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> arr;
vector<vector<int>> cache;

int f(int index, int diff)
{
    if(index == 0) {
        if(diff == 0) {
            return 0;
        } else {
            return -1;
        }
    }
    if(cache[index][diff] == -2) {
        int result = -1;
        int temp;
        if(diff >= arr[index]) {
            temp = f(index-1, diff-arr[index]);
            if(temp != -1) {
                result = max(result, temp+arr[index]);
            }
        } else {
            temp = f(index-1, arr[index]-diff);
            if(temp != -1) {
                result = max(result, temp+diff);
            }
        }
        temp = f(index-1, diff+arr[index]);
        if(temp != -1) {
            result = max(result, temp);
        }
        temp = f(index-1, diff);
        if(temp != -1) {
            result = max(result, temp);
        }
        cache[index][diff] = result;
    }
    return cache[index][diff];
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    cache.assign(n+1, vector<int>(500001, -2));

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    int answer = f(n, 0);
    if(answer == 0) {
        printf("-1\n");
    } else {
        printf("%d\n", answer);
    }
}