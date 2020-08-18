#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> parent;

int Find(int a)
{
    return (parent[a] == a) ? parent[a] : (parent[a] = Find(parent[a]));
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    (a < b) ? (parent[b] = a) : (parent[a] = b);
}

int main()
{
    scanf("%d %d", &n, &m);
    parent.resize(n+1);
    for(int i=1; i<=n; i++) {
        parent[i] = i;
    }

    int a, b, c;
    for(int i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        if(a == 0) {
            Union(b, c);
        } else {
            if(Find(b) == Find(c)) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
}