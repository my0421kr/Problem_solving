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
vector<int> answer;

void f(TreeNode * root)
{
    if(root != nullptr) {
        f(root->left);
        answer.push_back(root->val);
        f(root->right);
    }
}

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        answer.resize(0);
        f(root);
        return answer;
    }
};