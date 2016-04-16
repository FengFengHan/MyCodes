//
// Created by Han on 16/3/7.
//
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::queue;
using std::vector;
using std::endl;

class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node():val(0),left(NULL),right(NULL){} //it is must//////////////////
};

void inorder(Node* root, vector<Node*>& in)
{
    if(root == NULL){
        return;
    }
    inorder(root->left,in);
    in.push_back(root);
    inorder(root->right,in);
}

void LevelOrder(Node* root, vector<int>& res)
{
    std::queue<Node*> nodes;
    nodes.push(root);
    while(!nodes.empty()){
        Node* node = nodes.front();
        nodes.pop();
        res.push_back(node->val);
        if(node->left != NULL) {
            nodes.push(node->left);
        }
        if(node->right !=NULL){
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
    unsigned int N;
    cin >>N;
    vector<int> numbers(N);
    for(unsigned  int i=0; i < N;++i){
        cin >> numbers[i];
    }
    //Build tree
    int node_num = 0;
    Node* root = new Node;
    node_num += 1;
    queue<Node*> nodes;
    nodes.push(root);
    while(node_num < N){
       Node* node = nodes.front();
        nodes.pop();
        node->left = new Node;
        node_num += 1;
        nodes.push(node->left);
        if(node_num < N){
            node->right = new Node;
            node_num += 1;
            nodes.push(node->right);
        }
    }
    //in order traversal
    vector<Node*> in;
    inorder(root,in);
    //sort numbers;
    std::sort(numbers.begin(),numbers.end());
    //assign value
    for(size_t i=0;i< in.size();++i){
        (in[i])->val = numbers[i];
    }
    //level order
   vector<int> level;
    LevelOrder(root,level);
    //output
    cout << level[0];
    for(int i=1;i<N;++i){
        cout << " " << level[i];
    }
    cout << endl;
}
