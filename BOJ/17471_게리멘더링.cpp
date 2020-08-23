#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, e, cost[10], answer = 2e9;
vector<vector<int>> arr;
vector<int> visit;

int IsOk(int index, int path)
{
    visit[index] = 1;
    int len = arr[index].size(), result = 1;
    for(int i=0; i<len; i++) {
        int nextindex = arr[index][i];
        if(((1 << nextindex) & path) && (visit[nextindex] == 0)) {
            result += IsOk(nextindex, path);
        }
    }
    return result;
}

void DFS(int index, int path, int cnt)
{
    if(index == n) {
        int remain = ((1<<n)-1)-path;
        if(path != 0 && remain != 0) {
            visit.clear();
            visit.assign(n, 0);
            int start1, start2;
            for(int i=0; i<n; i++) {
                (path & (1<<i)) ? start1 = i : start2 = i;
            }
            if(IsOk(start1, path) == cnt && IsOk(start2, remain) == n-cnt) {
                int result1 = 0, result2 = 0;
                for(int i=0; i<n; i++) {
                    (path & (1<<i)) ? result1 += cost[i] : result2 += cost[i];
                }
                answer = min(answer, abs(result1 - result2));
            }
        }
    } else {
        DFS(index+1, path|(1<<index), cnt+1);
        DFS(index+1, path, cnt);
    }
}

int main()
{
    scanf("%d", &n);
    arr.resize(n);

    for(int i=0; i<n; i++) {
        scanf("%d", &cost[i]);
    }
    for(int i=0; i<n; i++) {
        scanf("%d", &e);
        arr[i].resize(e);
        for(int j=0; j<e; j++) {
            scanf("%d", &arr[i][j]);
            arr[i][j]--;
        }
    }

    DFS(0, 0, 0);

    if(answer == 2e9) {
        printf("-1\n");
    } else {
        printf("%d\n", answer);
    }
}