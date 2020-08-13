#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int head, tail, num;
} Node;

int n, m, seglen = 1;
vector<int> arr;
vector<Node> tree;

void Seglen(int index, int head, int tail)
{
    if(head == tail) {
        tree[index] = {head, tail, arr[head]};
    } else {
        int mid = (head+tail)/2;
        int left = index*2;
        int right = left+1;
        Seglen(left, head, mid);
        Seglen(right, mid+1, tail);
        tree[index] = {head, tail, max(tree[left].num, tree[right].num)};
    }
}

int f(int index, int head, int tail)
{
    Node cur = tree[index];
    if(cur.head == head && cur.tail == tail) {
        return cur.num;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(tail <= mid) {
            return f(index*2, head, tail);
        } else if(mid < head) {
            return f(index*2+1, head, tail);
        } else {
            return max(f(index*2, head, mid), f(index*2+1, mid+1, tail));
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    while(seglen < n) {
        seglen = (seglen << 1);
    }
    arr.resize(n+1);
    tree.resize(seglen*2);


    for(int i=1; i<=n; i++) {
        scanf("%d", &arr[i]);
    }

    Seglen(1, 1, n);
    for(int i=m; i<=n-m+1; i++) {
        printf("%d ", f(1, i-m+1, i+m-1));
    }
}