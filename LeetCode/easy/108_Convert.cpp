/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
TreeNode * f(int head, int tail, vector<int> &nums)
{

    TreeNode * pt;
    if(head == tail) {
        pt = new TreeNode(nums[head], nullptr, nullptr);
    } else if(head > tail) {
        pt = nullptr;
    } else {
        int mid = (head+tail)/2;
        pt = new TreeNode(nums[mid], f(head, mid-1, nums), f(mid+1, tail, nums));
    }
    return pt;
}

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return f(0, nums.size()-1, nums);
    }
};