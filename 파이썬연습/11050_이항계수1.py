def Combi(a, b):
    if f[a][b] == -1:
        if a == b or b == 0:
            f[a][b] = 1
        else:
            f[a][b] = Combi(a-1, b) + Combi(a-1, b-1)
    return f[a][b]

n, k = map(int, input().split())
f = [[-1 for _ in range(k+1)] for _ in range(n+1)]
print(Combi(n, k))