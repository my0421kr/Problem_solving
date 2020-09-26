import sys
import queue

def DFS(index):
    visit[index] = 1
    dfslist.append(index)
    for i in range(1, n+1):
        if arr[index][i] == 1 and visit[i] == 0:
            DFS(i)

def BFS(index):
    pq = queue.Queue()
    pq.put(index)
    visit[index] = 1
    while not pq.empty():
        nx = pq.get()
        bfslist.append(nx)
        visit[nx] = 1
        for i in range(1, n+1):
            if arr[nx][i] == 1 and visit[i] == 0:
                pq.put(i)
                visit[i] = 1

n, m, v = map(int, sys.stdin.readline().split())

arr = [[0 for _ in range(n+1)] for _ in range(n+1)]
for i in range(m):
    a, b = map(int, sys.stdin.readline().split())
    arr[a][b] = 1 
    arr[b][a] = 1

visit = [0 for _ in range(n+1)]
dfslist = []
DFS(v)
visit = [0 for _ in range(n+1)]
bfslist = []
BFS(v)


result1, result2 = "", ""
for x in dfslist:
    result1 += str(x) + " "
for x in bfslist:
    result2 += str(x) + " "
print(result1)
print(result2)
