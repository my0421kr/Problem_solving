#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    int head, tail;
    long long left, right;
} Node;

int n, seglen = 1;
vector<long long> arr;
vector<Node> tree;

void InitSeg(int index, int head, int tail)
{
    tree[index] = {head, tail, 0, 0};
    if(head != tail) {
        int mid = (head+tail)/2;
        InitSeg(index*2, head, mid);
        InitSeg(index*2+1, mid+1, tail);
    }
}

Node Print(int index, int target)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        return {target, target, cur.left, cur.right};
    } else {
        int mid = (cur.head+cur.tail)/2;
        Node temp;
        if(target <= mid) {
            temp = Print(index*2, target);
        } else {
            temp = Print(index*2+1, target);
        }
        return {target, target, cur.left+temp.left, cur.right+temp.right};
    }
}

void Update(int index, int head, int tail, long long left, long long right)
{
    if(head > tail) {
        return;
    }
    Node cur = tree[index];
    if(cur.head == head && cur.tail == tail) {
        tree[index].left += left;
        tree[index].right += right;
    } else {
        int mid = (cur.head+cur.tail)/2;
        if(tail <= mid) {
            Update(index*2, head, tail, left, right);
        } else if(mid < head) {
            Update(index*2+1, head, tail, left, right);
        } else {
            Update(index*2, head, mid, left, right);
            Update(index*2+1, mid+1, tail, left, right);
        }
    }
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);

    long long a;
    for(int i=1; i<=n; i++) {
        scanf("%lld", &a);
        arr[a] = i;
    }

    while(seglen < n) {
        seglen = (seglen << 1);
    }
    tree.resize(seglen*2);
    InitSeg(1, 1, seglen);

    long long head = 1, tail = n;
    for(int i=1; i<=n; i++) {
        if(i % 2 == 1) {
            Node updated = Print(1, arr[head]);
            printf("%lld\n", arr[head]-head+updated.left);
            Update(1, 1, arr[head]-1, 1, -1);
            head++;
        } else {
            Node updated = Print(1, arr[tail]);
            printf("%lld\n", tail-arr[tail]+updated.right);
            Update(1, arr[tail]+1, n, -1, 1);
            tail--;
        }
    }
}