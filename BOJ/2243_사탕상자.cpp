#include <iostream>
#include <vector>
#define MAX 1000000
using namespace std;

typedef struct _Node
{
    int num, head, tail;
} Node;

int n, seglen = 1;
vector<Node> tree;

void InitSeg(int index, int head, int tail)
{
    if(head != tail) {
        int mid = (head+tail)/2;
        InitSeg(index*2, head, mid);
        InitSeg(index*2+1, mid+1, tail);
    }
    tree[index] = {0, head, tail};
    return;
}

void Update(int index, int target, int newSum)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        if(target == cur.head) {
            tree[index].num += newSum;
        }
    } else if(cur.head <= target && target <= cur.tail) {
        Update(index*2, target, newSum);
        Update(index*2+1, target, newSum);
        tree[index].num += newSum;
    }
}

int Pop(int index, int count)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        return cur.head;
    } else {
        Node left = tree[index*2];
        Node right = tree[index*2+1];
        if(left.num >= count) {
            return Pop(index*2, count);
        } else {
            return Pop(index*2+1, count-left.num);
        }
    }
}

int main()
{
    scanf("%d", &n);

    while(seglen < MAX) {
        seglen = (seglen << 1);
    }
    tree.resize(seglen*2);
    InitSeg(1, 1, seglen);

    int a, b, target;
    for(int i=0; i<n; i++) {
        scanf("%d", &a);
        if(a == 1) {
            scanf("%d", &a);
            target = Pop(1, a);
            printf("%d\n", target);
            Update(1, target, -1);
        } else {
            scanf("%d %d", &a, &b);
            Update(1, a, b);
        }
    }
}