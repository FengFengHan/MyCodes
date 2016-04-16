//
// Created by Han on 16/3/11.
//
#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int val;
    Node* left;
    Node* right;
    Node(): val(0), left(NULL), right(NULL){}
    Node(int value){
        val = value;
        left = NULL; //it is must, else:left is not valid
        right = NULL;//it is must, else:right is not valid
    }
};

void InsertTree(Node* &root, int value)
{
   if(root == NULL){
       root = new Node(value);
   } else{
       if(value < root->val){
           InsertTree(root->left,value);
       }else{
           InsertTree(root->right,value);
       }
   }
}

void PreorderTraversal(Node* root, vector<int>& res)
{
    if(root == NULL){
        return;
    }
    res.push_back(root->val);
    PreorderTraversal(root->left,res);
    PreorderTraversal(root->right,res);
}

void PostorderTraversal(Node* root, vector<int>& res)
{
    if(root == NULL){
        return;
    }
    PostorderTraversal(root->left,res);
    PostorderTraversal(root->right,res);
    res.push_back(root->val);
}

void RootRLTraversal(Node* root, vector<int>& res)
{
    if(root == NULL){
        return;
    }
    res.push_back(root->val);
    RootRLTraversal(root->right,res);
    RootRLTraversal(root->left, res);
}

void RLRootTraversal(Node* root, vector<int>& res)
{
    if(root == NULL){
        return;
    }
    RLRootTraversal(root->right, res);
    RLRootTraversal(root->left,res);
    res.push_back(root->val);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    int N;
    cin >> N;
    vector<int> preorder(N);
    for(int i=0; i < N; ++i){
        cin >> preorder[i];
    }

    //Node* root = new Node(preorder[0]);
    Node* root = NULL;
    for(int i=0; i < preorder.size();++i){
        InsertTree(root,preorder[i]);
    }
    //traversal by preorder
    vector<int> ori_pre;
    PreorderTraversal(root, ori_pre);
    if(ori_pre == preorder){
        cout << "YES" << endl;
        vector<int> pos;
        PostorderTraversal(root,pos);
        cout << pos[0];
        for(int i=1; i< pos.size();++i){
            cout << " " << pos[i];
        }
        cout << endl;
        return 0;
    }
    //traversal by mirror
    vector<int> mirror_pre;
    RootRLTraversal(root, mirror_pre);
    if(mirror_pre == preorder){
        cout << "YES" << endl;
        vector<int> pos;
        RLRootTraversal(root,pos);
        cout << pos[0];
        for(int i=1; i< pos.size();++i){
            cout << " " << pos[i];
        }
        cout << endl;
        return 0;
    }
    //
    cout << "NO" << endl;
    return 0;
}
