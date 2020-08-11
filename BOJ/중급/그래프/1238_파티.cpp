#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct _Node
{
    int index, cost;
} Node;
typedef struct _cmp
{
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
} cmp;

int n, m, x;
int arr[1001][1001];
vector<int> last_dist1, last_dist2;

void Dijk(vector<int> &last_dist, int flag)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({x, 0});
    last_dist[x] = 0;

    while(!pq.empty()) {
        int index = pq.top().index;
        int cost = pq.top().cost;
        pq.pop();


        if(flag == 0) {
            for(int i=1; i<=n; i++) {
                if(arr[i][index] != 0 && arr[i][index] + cost < last_dist[i]) {
                    last_dist[i] = arr[i][index] + cost;
                    pq.push({i, arr[i][index] + cost});
                }
            }
        } else {
            for(int i=1; i<=n; i++) {
                if(arr[index][i] != 0 && arr[index][i] + cost < last_dist[i]) {
                    last_dist[i] = arr[index][i] + cost;
                    pq.push({i, arr[index][i] + cost});
                }
            }
        }
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &x);
    last_dist1.assign(n+1, 2e9);
    last_dist2.assign(n+1, 2e9);

    int head, tail, cost;
    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head][tail] = cost;
    }

    Dijk(last_dist1, 0);
    Dijk(last_dist2, 1);

    int answer = 0;
    for(int i=1; i<=n; i++) {
        answer = max(answer, last_dist1[i] + last_dist2[i]);
    }
    printf("%d\n", answer);
}