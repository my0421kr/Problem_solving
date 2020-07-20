#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, s;
vector<int> arr;

int main()
{
    scanf("%d %d", &n, &s);

    arr.resize(n);
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    int head = 0;
    int tail = -1;
    int temp_sum = 0;
    int result = 100001;
    while(1) {
        if(temp_sum < s) {
            tail++;
            if(tail == n) {
                break;
            }
            temp_sum += arr[tail];
        } else {
            result = min(result, tail - head + 1);
            temp_sum -= arr[head];
            head++;
        }
    }
    if(result == 100001) {
        printf("0\n");
    } else {
        printf("%d\n", result);
    }
}