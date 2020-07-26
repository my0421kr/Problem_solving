#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int t, n, m;
int line[501];
int parent[501];
bool arr[501][501];
vector<int> result;

void Init()
{
    result.clear();
    for(int i=1; i<=n; i++) {
        line[i] = 0;
        parent[i] = 0;
        for(int j=1; j<=n; j++) {
            arr[i][j] = false;
        }
    }
}

int Function()
{
    queue<int> pq;
    int count = 0, flag = 0;
    for(int i=1; i<=n; i++) {
        if(parent[i] == 0) {
            pq.push(i);
            result.push_back(i);
            count++;
            flag = 1;
        }
    }
    if(count != 1) {
        return count;
    }

    while(!pq.empty()) {
        int num = pq.front();
        pq.pop();

        count = 0;
        flag = 0;
        for(int i=1; i<=n; i++) {
            if(arr[num][i]) {
                flag = 1;
                parent[i]--;
                if(parent[i] == 0) {
                    count++;
                    pq.push(i);
                    result.push_back(i);
                }
            }
        }
        if(count == 0 && flag == 1) {
            return 0;
        } else if(count > 1) {
            return 2;
        }
    }
    return 1;
}

int main()
{
    scanf("%d", &t);

    for(int i=0; i<t; i++) {
        scanf("%d", &n);
        Init();
        for(int j=1; j<=n; j++) {
            scanf("%d", &line[j]);
        }
        for(int j=1; j<=n; j++) {
            for(int k=j+1; k<=n; k++) {
                arr[line[j]][line[k]] = true;
                parent[line[k]]++;
            }
        }

        scanf("%d", &m);
        int a, b, temp;
        for(int j=1; j<=m; j++) {
            scanf("%d %d", &a, &b);
            if(arr[a][b]) {
                parent[a]++;
                parent[b]--;
            } else {
                parent[a]--;
                parent[b]++;
            }
            arr[a][b] = !arr[a][b];
            arr[b][a] = !arr[b][a];
        }

        int answer = Function();
        if(answer == 1) {
            for(int i=0; i<n; i++) {
                printf("%d ", result[i]);
            }
        } else if(answer == 0){
            printf("IMPOSSIBLE");
        } else {
            printf("?");
        }
        printf("\n");
    }
}