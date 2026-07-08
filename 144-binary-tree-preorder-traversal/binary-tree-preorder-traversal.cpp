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
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
       vector<int> result;
        fun(root,result);
        return result;
        
    }
    void fun(TreeNode* root, vector<int>& result)
    {
        if(root==NULL)
        return;
        result.push_back(root-> val);
        fun(root->left,result);
        fun(root->right,result);

    }
};