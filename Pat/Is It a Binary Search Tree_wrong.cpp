//
// Created by Han on 16/3/7.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node():val(0),left(NULL),right(NULL) {}
};
vector<int> inorder(1000,-1);
vector<int> preorder(1000,-1);


Node* BuildTree(int s1, int e1, int s2, int e2)
{
    Node* root = new Node;
    int value = preorder[s1];
    root->val = value;
    s1 += 1;
    bool is_tree = false;
    for(int i=s2; i<e2; ++i){
        if(inorder[i] == value){
            is_tree = true;
            root->left = BuildTree(s1,i-s2 + s1,s2,i);
            root->right = BuildTree(e1 - e2 + i + 1,e1,i+1,e2);
            if((s2 < i && root->left == NULL) || (i+1 < e2 && root->right == NULL)){
                is_tree = false;
            }
        }
        if(is_tree){
            break;
        }
    }
    if(!is_tree){
        root = NULL;
    }
    return root;
}

bool cmp(int a, int b)
{
    return a > b;
}

void PostTrav(Node* root, vector<int>& post)
{
    if(root == NULL){
        return;
    }
    PostTrav(root->left,post);
    PostTrav(root->right,post);
    post.push_back(root->val);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    unsigned int N;
    cin >> N;

    for(unsigned  int i = 0;i< N;++i){
        cin >> preorder[i];
    }
    //assume that it is preorder of BST
    inorder = preorder;
    sort(inorder.begin(),inorder.begin() + N);
    Node* root = new Node;
    root = BuildTree(0,N,0,N);
    if(root == NULL){
        //assume that it is preorder of mirror BST
        sort(inorder.begin(), inorder.begin()+N, cmp);
        root = BuildTree(0,N,0,N);
    }
    //output result
    if(root == NULL){
        cout << "NO" << endl;
    }else{
        cout << "YES" << endl;
        vector<int> posorder;
        PostTrav(root,posorder);
        cout << posorder[0];
        for(int i = 1; i < posorder.size();++i){
            cout << " "  << posorder[i];
        }
        cout << endl;
    }
}
