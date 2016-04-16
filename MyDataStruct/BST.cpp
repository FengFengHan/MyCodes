//
// Created by Han on 16/3/25.
//
#include <iostream>

using namespace std;

class BST{
public:
   int val;
    BST* left;
    BST* right;
};

void DeleteNode(BST* &root);

bool DeletedBST(BST* &tree, int value)
{
    if(tree == NULL){//can not find
        return false;
    }
    if(value < tree->val){
        DeletedBST(tree->left,value);
    }else if(value > tree->val){
        DeletedBST(tree->right,value);
    }else{
        DeleteNode(tree);
        return true;
    }
}

void DeleteNode(BST* &root)
{
    BST* lc = root->left;
    BST* rc = root->right;
    if(lc == NULL && rc == NULL){// left child  and right child both NULL
        BST* tmp = root;
        root = NULL;
        delete tmp;
    }else if(lc == NULL || rc == NULL){// left child is NULL or right child is NULL
        BST* tmp = root;
        root = (lc == NULL ? rc : lc);
        delete tmp;
    }else{ // left child is tree and right child is tree
        //寻找root的前驱
        BST* pre = root;//记录前驱的父母
        BST* cur = root->right;
        while(cur->right != NULL){
            pre = cur;
            cur = cur->right;
        }
        root->val = cur->val;
        if(pre == root){
            pre->left = cur->left;
        }else{
            pre->right = cur->left;
        }
        delete cur;
    }
}