//
// Created by Han on 16/3/6.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int left_indexs[100];
int right_indexs[100];
int values[100];
//int childs_number[2];
class Node{
public:
    int value;
    Node* left;
    Node* right;
    int lchild_num;
    int rchild_num;
};

Node* BuildTree(int root_index)
{
   if(root_index == -1){
       return NULL;
   }
    Node* root = new Node;
    root->left = BuildTree(left_indexs[root_index]);
    root->right = BuildTree(right_indexs[root_index]);
    return root;
}

void GetChildNumber(Node* root)
{
    if(root->left == NULL){
        root->lchild_num = 0;
    }else{
        GetChildNumber(root->left);
        root->lchild_num = 1 + (root->left)->lchild_num + (root->left)->rchild_num;
    }
    if(root->right == NULL){
        root->rchild_num = 0;
    }else{
        GetChildNumber(root->right);
        root->rchild_num = 1 + (root->right)->lchild_num + (root->right)->rchild_num;
    }
}

void GetNodesValue(Node* root, int start, int end)
{
    if(root == NULL){
        return;
    }
    int smaller_num = root->lchild_num;
    root->value = values[start+smaller_num];
    GetNodesValue(root->left,start,start+smaller_num);
    GetNodesValue(root->right,start+smaller_num + 1,end);
}

void LevelTraversal(Node* root, vector<int>& res)
{
    queue<Node*> nodes;
    if(root != NULL){
        nodes.push(root);
    }
    while(! nodes.empty()){
       Node* node = nodes.front();
        nodes.pop();
        res.push_back(node->value);
        if(node->left != NULL){
          nodes.push(node->left);
        }
        if(node->right != NULL) {
            nodes.push(node->right);
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    int N;
    cin >> N;
    for(int i = 0;i<N;++i){
        cin >> left_indexs[i];
        cin >> right_indexs[i];
    }
    for(int i=0;i<N;++i){
        cin >> values[i];
    }
    //Build Tree
    Node* root = BuildTree(0);
    //sort numbers
    sort(values,values+N);
    //get child number
    GetChildNumber(root);
    //get root value
    GetNodesValue(root,0,N);
    //level order
    vector<int> res;
    LevelTraversal(root,res);
    cout << res[0];
    for(int i = 1; i < res.size();++i){
        cout << " " << res[i];
    }
    cout << endl;
}