//
// Created by Han on 16/3/3.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    int val;
    Node* left;
    Node* right;
};

int nodes_left[10];
int nodes_right[10];

Node* BuildTree(int root_val, int left_val, int right_val)
{
    if (root_val == -1){
        return NULL;
    }
    Node* tree = new Node;
    tree ->val = root_val;
    tree->left = BuildTree(left_val, nodes_left[left_val],nodes_right[left_val]);
    tree->right = BuildTree(right_val, nodes_left[right_val], nodes_right[right_val]);
    return tree;

}
//Node* InvertTree(Node* root)
//{
//    if(root == NULL){
//        return root;
//    }else if(root->left == NULL && root->right == NULL){
//        return root;
//    }
//    Node* invert_left = InvertTree(root->left);
//    Node* invert_right = InvertTree(root->right);
//    root->left = invert_right;
//    root->right = invert_left;
//    return root;
//}

void InvertTree(Node* &root)
{
    if(root == NULL){
        return;
    }
    Node* tmp = root->right;
    root->right = root->left;
    root->left = tmp;
    InvertTree(root->left);
    InvertTree(root->right);
}

void Inorder(Node*rt, vector<int>& res)
{
    if(rt == NULL){
        return;
    }
    Inorder(rt->left, res);
    res.push_back(rt->val);
    Inorder(rt->right, res);

}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    //read
    int N;
    cin >> N;
    vector<bool> if_root(N,true);
    char s[4];
    char lchild,rchild;
    for(int i=0;i < N;++i){
        cin >> lchild >> rchild;
        if(lchild != '-'){
            nodes_left[i] = lchild - '0';
            if_root[lchild - '0'] = false;
        } else{
            nodes_left[i] = -1;
        }
        if(rchild != '-'){
            nodes_right[i] = rchild - '0';
            if_root[rchild - '0'] = false;
        }else{
            nodes_right[i] = -1;
        }
    }
    int root_val;
    for(int i = 0; i < N;++i){
        if(if_root[i]){
            root_val = i;
            break;
        }
    }
    //build binary tree
    Node* root = BuildTree(root_val, nodes_left[root_val], nodes_right[root_val]);
    //invert binary tree
    InvertTree(root);
    //level order
    queue<Node *> Nodes;
    Nodes.push(root);
    Node* node;
    bool fir = true;
    while(!Nodes.empty()){
        node = Nodes.front();
        if(fir){
             printf("%d", node->val);
        }else{
            printf(" %d",node->val);
        }
        fir = false;
        Nodes.pop();
        if(node->left != NULL) {
            Nodes.push(node->left);
        }
        if(node->right != NULL) {
            Nodes.push(node->right);
        }
    }
    printf("\n");
    //in-order
    vector<int> in_sequence;
    Inorder(root, in_sequence);
    printf("%d", in_sequence[0]);
    for(int i = 1;i<in_sequence.size();++i){
        printf(" %d", in_sequence[i]);
    }
    printf("\n");
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif
}