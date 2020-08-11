#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _Node
{
    int num, index;
} Node;
typedef struct _Point
{
    int head, tail, cnt;
} Point;

int n, seglen = 1;
vector<int> arr;
vector<Node> temp1, temp2;
vector<Point> tree;

bool cmp(Node a, Node b)
{
    return a.num < b.num;
}

void InitSeg(int index, int head, int tail)
{
    tree[index] = {head, tail, 0};
    if(head != tail) {
        int mid = (head+tail)/2;
        InitSeg(index*2, head, mid);
        InitSeg(index*2+1, mid+1, tail);
    }
}

long long Count(int index, int head, int tail)
{
    Point cur = tree[index];
    if(cur.head == head && cur.tail == tail) {
        return cur.cnt;
    } else {
        int mid = (cur.head + cur.tail)/2;
        if(tail <= mid) {
            return Count(index*2, head, tail);
        } else if(mid < head) {
            return Count(index*2+1, head, tail);
        } else {
            return Count(index*2, head, mid) + Count(index*2+1, mid+1, tail);
        }
    }
}

void Update(int index, int target)
{
    Point cur = tree[index];
    tree[index].cnt++;
    if(cur.head != cur.tail) {
        int mid = (cur.head + cur.tail)/2;
        if(target <= mid) {
            Update(index*2, target);
        } else {
            Update(index*2+1, target);
        }
    }
    
    
}

int main()
{
    scanf("%d", &n);
    arr.resize(n+1);

    int a;
    long long answer = 0;
    for(int i=1; i<=n; i++) {
        scanf("%d", &a);
        temp1.push_back({a, i});
    }
    for(int i=1; i<=n; i++) {
        scanf("%d", &a);
        temp2.push_back({a, i});
    }

    sort(temp1.begin(), temp1.end(), cmp);
    sort(temp2.begin(), temp2.end(), cmp);
    for(int i=0; i<n; i++) {
        arr[temp1[i].index] = temp2[i].index;
    }

    while(seglen < n) {
        seglen = (seglen << 1);
    }
    tree.resize(seglen*2);
    InitSeg(1, 1, seglen);
    for(int i=1; i<=n; i++) {
        answer += Count(1, arr[i], n);
        Update(1, arr[i]);
    }
    printf("%lld\n", answer);

}