#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct _Node
{
    int num, head, tail;
} Node;

int n, m, seglen = 1;
vector<int> arr;
vector<Node> tree;

int InitSeg(int index, int head, int tail)
{
    if(head == tail) {
        tree[index] = {arr[head], head, tail};
    } else {
        int mid = (head+tail)/2;
        tree[index] = {min(InitSeg(index*2, head, mid), InitSeg(index*2+1, mid+1, tail)), head, tail};
    }
    return tree[index].num;
}

int Update(int index, int target, int newNum)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        tree[index].num = newNum;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(target <= mid) {
            tree[index].num = min(tree[index*2+1].num, Update(index*2, target, newNum));
        } else {
            tree[index].num = min(tree[index*2].num, Update(index*2+1, target, newNum));
        }
    }
    return tree[index].num;
}

int MinSeg(int index, int head, int tail)
{
    Node cur = tree[index];
    if(head == cur.head && tail == cur.tail) {
        return cur.num;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(tail <= mid) {
            return MinSeg(index*2, head, tail);
        } else if(mid < head) {
            return MinSeg(index*2+1, head, tail);
        } else {
            return min(MinSeg(index*2, head, mid), MinSeg(index*2+1, mid+1, tail));
        }
    }
}

int main()
{
    scanf("%d", &n);

    while(seglen < n) {
        seglen = (seglen << 1);
    }

    arr.assign(seglen+1, (int)2e9);
    tree.resize(seglen*2);

    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }
    InitSeg(1, 1, seglen);
    scanf("%d", &m);

    int query, a, b;
    for(int i=1; i<=m; i++) {
        scanf("%d %d %d", &query, &a, &b);
        if(query == 1) {
            Update(1, a, b);
        } else {
            printf("%d\n", MinSeg(1, a, b));
        }
    }
}