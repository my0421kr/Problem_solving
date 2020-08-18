#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int index, cost;
} Node;
typedef struct _Edge
{
    int prev, index, cost;
} Edge;
typedef struct _Info
{
    int first, second;
} Info;
typedef struct _cmp
{
    bool operator()(Edge a, Edge b) {
        return a.cost > b.cost;
    }
} cmp;

int n, m, answer = 2e9;
vector<int> visit, height;
vector<vector<int>> parent;
vector<vector<Info>> maxparent;
vector<Edge> checklist;
vector<vector<Node>> arr, tree;

void Kruskal()
{
    priority_queue<Edge, vector<Edge>, cmp> pq;
    pq.push({0, 1, 0});

    while(!pq.empty()) {
        int prev = pq.top().prev;
        int index = pq.top().index;
        int cost = pq.top().cost;
        int len = arr[index].size();
        pq.pop();

        if(visit[index] != -1) {
            checklist.push_back({prev, index, cost});
            continue;
        }
        visit[index] = cost;
        tree[prev].push_back({index, cost});

        for(int i=0; i<len; i++) {
            int nextindex = arr[index][i].index;
            int nextcost = arr[index][i].cost;

            if(nextindex != prev) {
                pq.push({index, nextindex, nextcost});
            }
        }
    }
}

void MakeHeight(int index, int cnt)
{
    height[index] = cnt;
    int len = tree[index].size();
    for(int i=0; i<len; i++) {
        MakeHeight(tree[index][i].index, cnt+1);
    }
}

void MakeParent()
{
    for(int i=1; i<=n; i++) {
        int len = tree[i].size();
        for(int j=0; j<len; j++) {
            parent[tree[i][j].index][0] = i;
            maxparent[tree[i][j].index][0] = {tree[i][j].cost, -1};
        }
    }
    parent[1][0] = 0;
    maxparent[1][0] = {0,-1};
}

int Parent(int a, int k)
{
    if(parent[a][k] == -1) {
        parent[a][k] = Parent(Parent(a, k-1), k-1);
    }
    return parent[a][k];
}

int UpParent(int a, int h)
{
    for(int i=0; i<20; i++) {
        if((1<<i) & h) {
            a = Parent(a, i);
        }
    }
    return a;
}

int LCA(int a, int b)
{
    if(height[a] > height[b]) {
        a = UpParent(a, height[a] - height[b]);
    } else if(height[b] > height[a]) {
        b = UpParent(b, height[b] - height[a]);
    }

    if(a == b) {
        return a;
    } else {
        int i, parent1, parent2;
        for(i=0; i<20; i++) {
            parent1 = Parent(a, i);
            parent2 = Parent(b, i);
            if(parent1 == parent2) {
                break;
            }
        }
        
        if(i == 0) {
            return parent1;
        } else {
            return LCA(Parent(a, i-1), Parent(b, i-1));
        }
    }
}

Info FirstSecond(Info a, Info b)
{
    Info result = {-1,-1};
    vector<int> temp;
    temp.push_back(a.first);
    temp.push_back(a.second);
    temp.push_back(b.first);
    temp.push_back(b.second);
    sort(temp.begin(), temp.end());
    result.first = temp[3];
    if(temp[2] != temp[3]) {
        result.second = temp[2];
    } else if(temp[1] != temp[3]) {
        result.second = temp[1];
    } else if(temp[0] != temp[3]) {
        result.second = temp[0];
    }
    temp.clear();
    return result;
}

Info MaxParent(int a, int k)
{
    if(a == 0) {
        return {0,0};
    }
    if(maxparent[a][k].first == -1) {
        Info info1 = MaxParent(a, k-1);
        Info info2 = MaxParent(Parent(a, k-1), k-1);
        maxparent[a][k] = FirstSecond(info1, info2);
    }
    return maxparent[a][k];
}

Info MaxLCA(int a, int b)
{
    int h = height[a] - height[b];
    if(h == 0) {
        return {-1,-1};
    } else {
        Info result = {-1,-1};
        for(int i=0; i<20; i++) {
            if((1<<i) & h) {
                result = FirstSecond(result, MaxParent(a, i));
                a = Parent(a, i);
            }
        }
        return result;
    }
}

void SecondMST()
{
    int len = checklist.size();
    for(int i=0; i<len; i++) {
        int lca = LCA(checklist[i].prev, checklist[i].index);
        Info maxlca = FirstSecond(MaxLCA(checklist[i].prev, lca), MaxLCA(checklist[i].index, lca));
        if(checklist[i].cost == maxlca.first) {
            if(maxlca.second != -1) {
                answer = min(answer, checklist[i].cost - maxlca.second);
            }
        } else {
            answer = min(answer, checklist[i].cost - maxlca.first);
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    arr.resize(n+1);
    tree.resize(n+1);
    visit.assign(n+1, -1);
    height.resize(n+1);
    parent.assign(n+1, vector<int>(20, -1));
    maxparent.assign(n+1, vector<Info>(20, {-1, -1}));
    
    int head, tail, cost;
    for(int i=1; i<=m; i++) {
        scanf("%d %d %d", &head, &tail, &cost);
        arr[head].push_back({tail, cost});
        arr[tail].push_back({head, cost});
    }

    Kruskal();

    for(int i=1; i<=n; i++) {
        if(visit[i] == -1) {
            printf("-1\n");
            return 0;
        }
    }

    MakeHeight(1, 0);
    MakeParent();
    SecondMST();

    if(answer == 2e9) {
        printf("-1\n");
    } else {
        for(int i=1; i<=n; i++) {
            answer += visit[i];
        }
        printf("%d\n", answer);
    }
}