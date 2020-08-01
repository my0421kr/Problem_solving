#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
    long long num;
    int head, tail;
} Node;

int n, m, k;
vector<long long> arr;
vector<Node> tree;

void InitSeg(int index, int head, int tail)
{
    if(head == tail) {
        tree[index] = {arr[head], head, tail};
        return;
    }

    int mid = (head+tail)/2;
    int left = index*2;
    int right = left+1;

    InitSeg(left, head, mid);
    InitSeg(right, mid+1, tail);
    tree[index] = {tree[left].num + tree[right].num, head, tail};
}

long long Update(int index, int target, int newNum)
{
    Node cur = tree[index];
    if(cur.head == cur.tail) {
        if(cur.head == target) {
            tree[index].num = newNum;
            return newNum;
        }
    } else if(cur.head <= target && target <= cur.tail) {
        tree[index].num = Update(index*2, target, newNum) + Update(index*2 + 1, target, newNum);
    }
    return tree[index].num;
}

long long Sum(int index, int head, int tail)
{
    Node cur = tree[index];
    int mid = (cur.head + cur.tail)/2;
    if(head == cur.head && tail == cur.tail) {
        return cur.num;
    } else if(tail <= mid) {
        return Sum(index*2, head, tail);
    } else if(mid < head) {
        return Sum(index*2+1, head, tail);
    } else {
        return Sum(index*2, head, mid) + Sum(index*2+1, mid+1, tail);
    }

}

int main()
{
    scanf("%d %d %d", &n, &m, &k);

    int seglen = 1;
    while(seglen < n) {
        seglen = (seglen << 1);
    }

    arr.assign(seglen + 1, 0);
    tree.resize(2*seglen);
    for(int i=1; i<=n; i++) {
        scanf("%lld", &arr[i]);
    }

    InitSeg(1, 1, seglen);

    int a, b, c;
    for(int i=0; i<m+k; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) {
            Update(1, b, c);
        } else {
            printf("%lld\n", Sum(1, b, c));
        }
    }

}