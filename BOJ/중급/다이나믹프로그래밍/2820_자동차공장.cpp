#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int num, head, tail;
} Node;

int n, m, seglen = 1;
vector<vector<int>> tree;
vector<int> cost, ha, count, inverse;
vector<Node> segtree;

int CountChild(int index)
{
    int len = tree[index].size();
    for(int i=0; i<len; i++) {
        count[index] += CountChild(tree[index][i]);
    }
    return count[index]+1;
}

void DFS(int index)
{
    ha.push_back(index);
    inverse[index] = ha.size()-1;
    int len = tree[index].size();
    for(int i=0; i<len; i++) {
        DFS(tree[index][i]);
    }
}

void InitSeg(int index, int head, int tail)
{
    segtree[index] = {0, head, tail};
    if(head != tail) {
        int mid = (head+tail)/2;
        InitSeg(index*2, head, mid);
        InitSeg(index*2+1, mid+1, tail);
    }
}

void Update(int index, int head, int tail, int num)
{
    if(head > tail) {
        return;
    }
    Node cur = segtree[index];
    if(cur.head == head && cur.tail == tail) {
        segtree[index].num += num;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(tail <= mid) {
            Update(index*2, head, tail, num);
        } else if(mid < head) {
            Update(index*2+1, head, tail, num);
        } else {
            Update(index*2, head, mid, num);
            Update(index*2+1, mid+1, tail, num);
        }
    }
}

int Cal(int index, int target)
{
    Node cur = segtree[index];
    if(cur.head == cur.tail) {
        return cur.num;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(target <= mid) {
            return Cal(index*2, target) + cur.num;
        } else {
            return Cal(index*2+1, target) + cur.num;
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    cost.resize(n+1);
    tree.resize(n+1);
    count.assign(n+1, 0);
    inverse.resize(n+1);

    scanf("%d", &cost[1]);
    int a, b;
    for(int i=2; i<=n; i++) {
        scanf("%d %d", &a, &b);
        cost[i] = a;
        tree[b].push_back(i);
    }

    CountChild(1);
    ha.push_back(0);
    DFS(1);

    while(seglen < n) {
        seglen = (seglen << 1);
    }
    segtree.resize(seglen*2);
    InitSeg(1, 1, n);

    char c;
    for(int i=1; i<=m; i++) {
        getchar();
        c = getchar();
        if(c == 'p') {
            scanf("%d %d", &a, &b);
            Update(1, inverse[a]+1, inverse[a]+count[a], b);
        } else {
            scanf("%d", &a);
            printf("%d\n", Cal(1, inverse[a]) + cost[a]);
        }
    }
}