#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int head, tail;
    long long num;
    int numindex;
} Node;

int n, seglen;
vector<long long> arr;
vector<Node> tree;

Node InitSeg(int index, int head, int tail)
{
    if(head == tail) {
        tree[index] = {head, tail, arr[head], head};
    } else {
        int mid = (head+tail)/2;
        Node temp1 = InitSeg(index*2, head, mid);
        Node temp2 = InitSeg(index*2+1, mid+1, tail);
        if(temp1.num < temp2.num) {
            tree[index] = {head, tail, temp1.num, temp1.numindex};
        } else {
            tree[index] = {head, tail, temp2.num, temp2.numindex};
        }
    }
    return tree[index];
}

Node Search(int index, int head, int tail)
{
    Node cur = tree[index];
    if(cur.head == head && cur.tail == tail) {
        return cur;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(tail <= mid) {
            return Search(index*2, head, tail);
        } else if(mid < head) {
            return Search(index*2+1, head, tail);
        } else {
            Node temp1 = Search(index*2, head, mid);
            Node temp2 = Search(index*2+1, mid+1, tail);
            if(temp1.num < temp2.num) {
                return temp1;
            } else {
                return temp2;
            }
        }
    }
}

long long f(int head, int tail)
{
    if(head > tail) {
        return 0;
    } else if(head == tail) {
        return arr[head];
    }
    Node thr = Search(1, head, tail);
    long long num1 = thr.num * (tail - head + 1);
    long long num2 = f(head, thr.numindex-1);
    long long num3 = f(thr.numindex+1, tail);
    return max(num1, max(num2, num3));
}

int main()
{
    while(1) {

        scanf("%d", &n);
        arr.clear();
        arr.resize(n+1);

        if(n == 0) {
            break;
        }

        for(int i=1; i<=n; i++) {
            scanf("%lld", &arr[i]);
        }

        seglen = 1;
        while(seglen < n) {
            seglen = (seglen << 1);
        }
        tree.clear();
        tree.resize(seglen*2);
        InitSeg(1, 1, n);
        printf("%lld\n", f(1, n));
    }
}