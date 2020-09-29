class Solution {
public:
    void f(int index, vector<int> &nums, vector<int> &result, vector<vector<int>> &answer) {
        if(index == nums.size()) {
            answer.push_back(result);
            return;
        }
        result.push_back(nums[index]);
        f(index+1, nums, result, answer);
        result.pop_back();
        f(index+1, nums, result, answer);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> result(0);
        vector<vector<int>> answer(0, vector<int>(0));
        f(0, nums, result, answer);
        return answer;
    }
};