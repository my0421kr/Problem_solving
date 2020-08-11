#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n;
vector<int> arr, lis, index, pre, result;

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);
    lis.assign(n+1, 2e9);
    index.resize(n+1);
    pre.resize(n+1);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    lis[1] = arr[1];
    index[1] = 1;
    pre[1] = 0;
    int answer = 1;
    for(int i=2; i<=n; i++) {
        int target = lower_bound(lis.begin()+1, lis.end(), arr[i]) - lis.begin();
        answer = max(answer, target);
        if(arr[i] < lis[target]) {
            lis[target] = arr[i];
            index[target] = i;
            pre[i] = index[target-1];
        }
    }

    printf("%d\n", answer);
    int target = index[answer];

    while(target != 0) {
        result.push_back(arr[target]);
        target = pre[target];
    }

    int len = result.size();
    for(int i=len-1; i>=0; i--) {
        printf("%d ",  result[i]);
    }
}