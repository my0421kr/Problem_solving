#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

int n;
stack<int> ps;

int main()
{
    scanf("%d", &n);

    char str[20];
    for(int i=0; i<n; i++) {
        scanf("%s", str);
        if(!strcmp(str, "push")) {
            int a;
            scanf("%d", &a);
            ps.push(a);
        } else if(!strcmp(str, "pop")) {
            if(ps.empty()) {
                printf("-1\n");
            } else {
                printf("%d\n", ps.top());
                ps.pop();
            }
        } else if(!strcmp(str, "size")) {
            printf("%d\n", (int)ps.size());
        } else if(!strcmp(str, "empty")) {
            if(ps.empty()) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        } else if(!strcmp(str, "top")) {
            if(ps.empty()) {
                printf("-1\n");
            } else {
                printf("%d\n", ps.top());
            }
        }
    }
}