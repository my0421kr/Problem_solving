vector<int> dp(46, -1);

class Solution {
public:
    int climbStairs(int n) {
        if(dp[n] == -1) {
            if(n == 1 || n == 2) {
                dp[n] = n;
            } else {
                dp[n] = climbStairs(n-1) + climbStairs(n-2);
            }
        }
        return dp[n];
    }
};