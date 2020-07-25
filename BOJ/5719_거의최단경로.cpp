#include <iostream>
#include <queue>
#include <vector>
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

int n, m;
int first, last;
int arr[501][501];
vector<int> last_dist;

void Init_Array()
{
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            arr[i][j] = 0;
        }
    }
}

void Init_Dist()
{
    last_dist.clear();
    last_dist.assign(n, (int)2e9);
}

void Dijk()
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({first, 0});
    last_dist[first] = 0;

    while(!pq.empty()) {
        int num = pq.top().num;
        int cost = pq.top().cost;
        pq.pop();

        for(int i=0; i<n; i++) {
            if(arr[num][i] != 0 && (cost + arr[num][i] < last_dist[i]) ) {
                last_dist[i] = cost + arr[num][i];
                pq.push({i, last_dist[i]});
            }
        }
    }
}

void EraseDijk()
{
    queue<int> pq;
    pq.push(last);

    while(!pq.empty()) {
        int target = pq.front();
        pq.pop();

        for(int i=0; i<n; i++) {
            if(arr[i][target] != 0 && (last_dist[target] == arr[i][target] + last_dist[i]) ) {
                pq.push(i);
                arr[i][target] = 0;
            }
        }
    }
}

int main()
{
    int head, tail;
    while(1) {
        scanf("%d %d", &n, &m);
        if(n == 0 && m == 0) {
            break;
        }
        scanf("%d %d", &first, &last);
        Init_Array();
        Init_Dist();
        for(int i=0; i<m; i++) {
            scanf("%d %d", &head, &tail);
            scanf("%d", &arr[head][tail]);
        }
        Dijk();
        EraseDijk();
        Init_Dist();
        Dijk();
        if(last_dist[last] == 2e9) {
            printf("-1\n");
        } else {
            printf("%d\n", last_dist[last]);
        }
    }
}