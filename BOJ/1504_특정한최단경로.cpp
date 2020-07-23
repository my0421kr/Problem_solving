#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int num, cost;
} Node;

typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

int n, e;
vector<int> last_result;
vector<vector<Node>> arr;

void Init()
{
    last_result.clear();
    last_result.assign(n+1, 2e9);
}

int Dijk(int start, int end)
{
    Init();
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({start, 0});

    while(!pq.empty()) {
        int num = pq.top().num;
        int cost = pq.top().cost;
        pq.pop();

        if(cost < last_result[num]) {
            last_result[num] = cost;
            int len = (int)arr[num].size();
            for(int i=0; i<len; i++) {
                pq.push({arr[num][i].num, arr[num][i].cost + cost});
            }
        }
    }
    return last_result[end];
}

int main()
{
    scanf("%d %d", &n, &e);
    arr.resize(n+1);

    int head, tail, cost;
    int mid1, mid2;
    int temp1, temp2, temp3;
    int result = 2e9;
    for(int i=0; i<e; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
        arr[tail].push_back({head, cost});
    }
    scanf("%d %d", &mid1, &mid2);

    temp1 = Dijk(1, mid1);
    temp2 = Dijk(mid1, mid2);
    temp3 = Dijk(mid2, n);

    if(temp1 != 2e9 && temp2 != 2e9 && temp3 != 2e9) {
        result = min(result, temp1 + temp2 + temp3);
    }

    temp1 = Dijk(1, mid2);
    temp2 = Dijk(mid2, mid1);
    temp3 = Dijk(mid1, n);

    if(temp1 != 2e9 && temp2 != 2e9 && temp3 != 2e9) {
        result = min(result, temp1 + temp2 + temp3);
    }

    if(result == 2e9) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

}