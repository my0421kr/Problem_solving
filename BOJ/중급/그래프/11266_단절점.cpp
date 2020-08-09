#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, start, cur_order = 0;
vector<vector<int>> arr;
vector<int> result, visit, order;

int DFS(int index)
{
    order[index] = ++cur_order;
    int len = arr[index].size();
    int count = 0;
    int low = order[index];

    for(int i=0; i<len; i++) {
        if(visit[arr[index][i]] == 0) {
            count++;
            visit[arr[index][i]] = 1;
            int temp = DFS(arr[index][i]);
            low = min(low, temp);
            if(order[index] <= temp) {
                result[index] = 1;
            }
        } else {
            low = min(low, order[arr[index][i]]);
        }
    }
    if(start == index) {
        if(count > 1) {
            result[index] = 1;
        } else {
            result[index] = 0;
        }
    }
    return low;
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.resize(n+1);
    visit.assign(n+1, 0);
    order.resize(n+1);
    result.assign(n+1, 0);

    int a, b;
    for(int i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    for(int i=1; i<=n; i++) {
        if(visit[i] == 0) {
            start = i;
            visit[i] = 1;
            DFS(i);
        }
    }

    int answer = 0;
    for(int i=1; i<=n; i++) {
        if(result[i] == 1) {
            answer++;
        }
    }
    printf("%d\n", answer);
    for(int i=1; i<=n; i++) {
        if(result[i] == 1) {
            printf("%d ", i);
        }
    }
}