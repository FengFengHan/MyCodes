//
// Created by Han on 16/3/5.
//
#include <iostream>
#include <queue>
using namespace std;
 // Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> nodes;
        if(root != NULL) {
            nodes.push(root);
        }
        while(!nodes.empty()){
            TreeNode* node = nodes.front();
            nodes.pop();
            TreeNode* tmp = node->left;
            node->left = node->right;
            node->right = tmp;
            if(node->left != NULL) {
                nodes.push(node->left);
            }
            if(node->right != NULL) {
                nodes.push(node->right);
            }

        }
        return root;
    }
};
