#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void f(int cnt, vector<int> &nums, vector<int> &result, vector<bool> &visit, vector<vector<int>> &answer) {
        int n = nums.size();
        if(cnt == n) {
            answer.push_back(result);
            return;
        }
        for(int i=0; i<n; i++) {
            if(!visit[i]) {
                visit[i] = true;
                result.push_back(nums[i]);
                f(cnt+1, nums, result, visit, answer);
                result.pop_back();
                visit[i] = false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> visit(nums.size(), false);
        vector<int> result(0);
        vector<vector<int>> answer(0, vector<int>(0));
        f(0, nums, result, visit, answer);
        return answer;
    }
};