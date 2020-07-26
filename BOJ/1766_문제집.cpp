#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct _cmp
{
    bool operator()(int a, int b) {
        return a > b;
    }
} cmp;

int n, m;
vector<int> parent;
vector<vector<int>> arr;

void Function()
{
    priority_queue<int, vector<int>, cmp> pq;
    for(int i=1; i<=n; i++) {
        if(parent[i] == 0) {
            pq.push(i);
        }
    }

    while(!pq.empty()) {
        int num = pq.top();
        int len = (int)arr[num].size();
        pq.pop();
        printf("%d ", num);

        for(int i=0; i<len; i++) {
            parent[arr[num][i]]--;
            if(parent[arr[num][i]] == 0) {
                pq.push(arr[num][i]);
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    parent.assign(n+1, 0);
    arr.resize(n+1);

    int a, b;
    for(int i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        arr[a].push_back(b);
        parent[b]++;
    }

    Function();
}