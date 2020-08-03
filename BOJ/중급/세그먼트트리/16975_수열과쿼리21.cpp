#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    long long num;
    int head, tail;
} Node;

int n, m, seglen = 1;
vector<long long> arr;
vector<Node> tree;

void InitSeg(int index, int head, int tail)
{
    if(head != tail) {
        int mid = (head+tail)/2;
        InitSeg(index*2, head, mid);
        InitSeg(index*2+1, mid+1, tail);
    }
    tree[index] = {0, head, tail};
}

void Update(int index, int head, int tail, long long k)
{
    Node cur = tree[index];
    if(head == cur.head && tail == cur.tail) {
        tree[index].num += k;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(tail <= mid) {
            Update(index*2, head, tail, k);
        } else if(mid < head) {
            Update(index*2+1, head, tail, k);
        } else {
            Update(index*2, head, mid, k);
            Update(index*2+1, mid+1, tail, k);
        }
    }
}

long long SumSeg(int index, int target)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        return cur.num;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(target <= mid) {
            return cur.num + SumSeg(index*2, target);
        } else {
            return cur.num + SumSeg(index*2+1, target);
        }
    }
}

int main()
{
    scanf("%d", &n);

    while(seglen < n) {
        seglen = (seglen << 1);
    }

    arr.assign(seglen+1, 0);
    tree.resize(seglen*2);

    for(int i=1; i<=n; i++) {
        scanf("%lld", &arr[i]);
    }

    InitSeg(1, 1, seglen);

    scanf("%d", &m);
    int query, a, b, c;
    for(int i=1; i<=m; i++) {
        scanf("%d", &query);
        if(query == 1) {
            scanf("%d %d %d", &a, &b, &c);
            Update(1, a, b, c);
        } else {
            scanf("%d", &a);
            printf("%lld\n", arr[a] + SumSeg(1, a));
        }
    }

}