#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct _Node
{
    int num, cost;
} Node;

vector<int> job;
vector<vector<int>> arr;
vector<int> parent;
vector<int> last_dist;
int n, result = 0;

void Function()
{
    queue<Node> pq;
    for(int i=1; i<=n; i++) {
        if(parent[i] == 0) {
            pq.push({i, job[i]});
            last_dist[i] = job[i];
        }
    }
    while(!pq.empty()) {
        int num = pq.front().num;
        int cost = pq.front().cost;
        int len = (int)arr[num].size();
        pq.pop();

        for(int i=0; i<len; i++) {
            last_dist[arr[num][i]] = max(last_dist[arr[num][i]], cost + job[arr[num][i]]);
            parent[arr[num][i]]--;
            if(parent[arr[num][i]] == 0) {
                pq.push({arr[num][i], last_dist[arr[num][i]]});
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    job.resize(n+1);
    arr.resize(n+1);
    last_dist.assign(n+1, 0);
    parent.assign(n+1, 0);

    for(int i=1; i<=n; i++) {
        int temp;
        scanf("%d", &job[i]);
        scanf("%d", &parent[i]);
        for(int j=0; j<parent[i]; j++) {
            scanf("%d", &temp);
            arr[temp].push_back(i);
        }
    }

    Function();
    for(int i=1; i<=n; i++) {
        result = max(result, last_dist[i]);
    }
    printf("%d\n", result);
}