#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int index;
    long long cost;
} Node;

int n, m;
vector<vector<Node>> arr;
vector<long long> last_dist;

bool Bell()
{
    bool result = false;
    for(int i=1; i<=n; i++) {
        if(last_dist[i] != 2e18) {
            int len = arr[i].size();
            for(int j=0; j<len; j++) {
                int nextindex = arr[i][j].index;
                long long nextcost = arr[i][j].cost + last_dist[i];
                if(nextcost < last_dist[nextindex]) {
                    result = true;
                    last_dist[nextindex] = nextcost;
                }
            }
        }
    }
    return result;
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.resize(n+1);
    last_dist.assign(n+1, (long long)2e18);

    int a, b;
    long long c;
    for(int i=1; i<=m; i++) {
        scanf("%d %d %lld", &a, &b, &c);
        arr[a].push_back({b, c});
    }

    last_dist[1] = 0;
    for(int i=1; i<=n-1; i++) {
        Bell();
    }
    if(Bell()) {
        printf("-1\n");
    } else {
        for(int i=2; i<=n; i++) {
            if(last_dist[i] == (long long)2e18) {
                printf("-1\n");
            } else {
                printf("%lld\n", last_dist[i]);
            }
        }
    }

}