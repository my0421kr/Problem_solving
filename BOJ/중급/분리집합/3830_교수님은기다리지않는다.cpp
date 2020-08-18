#include <iostream>
#include <vector>
using namespace std;

typedef struct _Node
{
	int index, cost;
} Node;

int n, m;
Node parent[100001];

Node Find(int a)
{
	if(a == parent[a].index)
		return parent[a];
	Node temp = Find(parent[a].index);
	parent[a].index = temp.index;
	parent[a].cost += temp.cost;
	return parent[a];
}

void Union(int a, int b, int w)
{
	Node temp = Find(a);
	parent[b].index = temp.index;
	parent[b].cost = temp.cost + w;
}

void Init_Parent()
{
	int i;
	for(i=1; i<=n; i++){
		parent[i].index = i;
		parent[i].cost = 0;
	}
}

int main()
{
	int i, a, b, w;
	char pr;
	Node temp1, temp2;
	scanf("%d %d", &n, &m);
	while(n != 0){
		Init_Parent();
		for(i=1; i<=m; i++){
			getchar();
			pr = getchar();

			scanf("%d %d", &a, &b);
			temp1 = Find(a);
			temp2 = Find(b);

			if(pr == '!'){
				scanf("%d", &w);
				if(temp1.index < temp2.index)
					Union(temp1.index, temp2.index, temp1.cost + w - parent[b].cost);
				else
					Union(temp2.index, temp1.index, -(temp1.cost + w - parent[b].cost));
			}
			else{
				if(temp1.index != temp2.index)
					printf("UNKNOWN\n");
				else
					printf("%d\n", temp2.cost - temp1.cost);
			}
		}
		scanf("%d %d", &n, &m);
	}
}