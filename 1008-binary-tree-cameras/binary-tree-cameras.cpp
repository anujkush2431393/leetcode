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
    int minCameraCover(TreeNode* root) {
        int count = 0;
        if(fun(root , count)== -1)
        return count+1;
        else
        return count;
    
    }
    int fun(TreeNode* root , int & count){
        if (root == NULL)
        return 1;
        int l =fun(root->left, count);
        int r = fun(root->right, count);
        if(l == -1 || r == -1)
        {
            count++;
            return 0;
        }
        if(l == 0 || r == 0)
        return 1;
        return -1;
        }
    };