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

Node* getNode(int *postorder, int s1,int e1, int *inorder, int s2, int e2){
	if(s1 >= e1){
		return NULL;
	}
	Node *node = new Node;
	node->val = postorder[e1-1];
	int leftCount = 0;
	for(int i = s2; i < e2; ++i){
		if(inorder[i] == postorder[e1-1]){
			break;
		}
		leftCount += 1;
	}
	node->left = getNode(postorder,s1,s1 + leftCount,inorder,s2,s2+leftCount);
	node->right = getNode(postorder,s1+leftCount,e1-1,inorder,s2+leftCount+1,e2);
	return node;
}
int main()
{
	int N;
	cin >> N;
	int postorder[30];
	int inorder[30];
	for(int i = 0; i < N;++i){
		cin >> postorder[i];
	}
	for(int i = 0; i < N;++i){
		cin >> inorder[i];
	}
	Node* root = getNode(postorder,0,N,inorder,0,N);

    //level traversal
	queue<Node*> nodes;
	nodes.push(root);
	bool fir = true;
	while(!nodes.empty()){
		Node *node = nodes.front();
		if(fir){
			cout << node->val;
			fir = false;
		}else{
			cout << " " << node->val;
		}
		if(node -> left != NULL){
			nodes.push(node->left);
		}
		if(node->right != NULL){
			nodes.push(node->right);
		}
		nodes.pop();
	}
	cout << endl;
    return 0;
}