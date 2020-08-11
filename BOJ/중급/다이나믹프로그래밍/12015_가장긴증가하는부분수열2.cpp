#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
vector<int> arr, lis;

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    lis.assign(n+1, 2e9);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    lis[1] = arr[1];
    int answer = 1;
    for(int i=2; i<=n; i++) {
        int target = lower_bound(lis.begin()+1, lis.end(), arr[i]) - lis.begin();
        answer = max(answer, target);
        if(arr[i] < lis[target]) {
            lis[target] = arr[i];
        }
    }

    printf("%d\n", answer);
}