#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int head, tail;
} Node;

int n, m, cur_order = 0;
vector<vector<int>> arr;
vector<int> order, parent, low;
vector<Node> result;

bool cmp(Node a, Node b)
{
    if(a.head < b.head) {
        return true;
    } else if(a.head == b.head) {
        return (a.tail < b.tail);
    } else {
        return false;
    }
}

void Init()
{
    arr.resize(n+1);
    order.resize(n+1);
    parent.resize(n+1);
    low.resize(n+1);
}

void DFS(int index)
{
    order[index] = ++cur_order;
    low[index] = cur_order;

    int len = arr[index].size();
    for(int i=0; i<len; i++) {
        if(parent[index] == arr[index][i]) {
            continue;
        }

        if(order[arr[index][i]] == 0) {
            parent[arr[index][i]] = index;
            DFS(arr[index][i]);

            if(low[arr[index][i]] > order[index]) {
                result.push_back({min(index, arr[index][i]), max(index, arr[index][i])});
            }

            low[index] = min(low[index], low[arr[index][i]]);
        } else {
            low[index] = min(low[index], order[arr[index][i]]);
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    Init();

    int a, b;
    for(int i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        arr[a].push_back(b);
        arr[b].push_back(a);
    }

    DFS(1);

    int answer = result.size();
    printf("%d\n", answer);
    sort(result.begin(), result.end(), cmp);
    for(int i=0; i<answer; i++) {
        printf("%d %d\n", result[i].head, result[i].tail);
    }
}