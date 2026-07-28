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
 
class Solution {
public:
 void preorder(TreeNode* root , vector<int> &v){
    if(root==NULL)
 {
    v.push_back(10001);
    return;
    
 }  
 else{
    v.push_back(root->val);
    preorder(root->left,v);
    preorder(root->right,v);
 } 
 }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        vector<int> vp,vq;
        preorder(p, vp);
        preorder(q, vq);
        if(vp == vq)
        return true;
        else 
        return false;
        
        
    }
};*/
class Solution {
public:
 bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p==NULL && q == NULL)
      return true;
      if(p== NULL || q==NULL)
      return false;
      return(p->val == q->val)&&
      isSameTree(p->left, q-> left)&&
      isSameTree(p-> right,q->right);
      

      }
};
       