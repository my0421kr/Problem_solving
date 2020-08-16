#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> tree;
vector<int> cache;

int f(int index)
{
    if(cache[index] == -1) {
        int result = 0;
        int len = tree[index].size();
        vector<int> temp;
        if(len == 0) {
            result = 0;
        } else {
            for(int i=0; i<len; i++) {
                temp.push_back(f(tree[index][i]));
            }
            sort(temp.begin(), temp.end());
            for(int i=0; i<len; i++) {
                temp[i] += len-i;
            }
            for(int i=0; i<len; i++) {
                result = max(result, temp[i]);
            }
            temp.clear();
        }
        cache[index] = result;
    }
    return cache[index];
}

int main()
{
    scanf("%d", &n);
    tree.resize(n);
    cache.assign(n, -1);

    int a;
    scanf("%d", &a);
    for(int i=1; i<n; i++) {
        scanf("%d", &a);
        tree[a].push_back(i);
    }

    printf("%d\n", f(0));
}