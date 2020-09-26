import sys

def combi(n, m):
    if dp[n][m] == -1:
        if n == m or m == 0:
            dp[n][m] = 1
        else:
            dp[n][m] = combi(n-1, m) + combi(n-1, m-1)
    return dp[n][m]

n, m = map(int, sys.stdin.readline().split())
dp = [[-1 for _ in range(n+1)] for _ in range(n+1)]
print(combi(n, m))