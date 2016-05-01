//
// Created by Han on 16/4/19.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class LongestPath {
public:
    int findPath(TreeNode* root) {
        // write code here
        int max_len = 0;
        GetSingleLen(root,max_len);
        return  max_len;
    }
    static int GetSingleLen(TreeNode* rt,int & max_len)
    {
        if(rt == NULL) {
            return 0;
        }
        int single_len = 1;
        int double_len = 1;
        if(rt->left != NULL) {
            int left_len = GetSingleLen(rt->left, max_len);
            if(rt->val == (rt->left)->val){
                single_len += left_len;
                double_len += left_len;
            }
        }
        if(rt->right != NULL) {
            int right_len = GetSingleLen(rt->right, max_len);
            if (rt->val == (rt->right)->val) {
                if (right_len >= single_len) {
                    single_len = right_len + 1;
                }
                double_len += right_len;
            }
        }
        if(double_len > max_len){
            max_len = double_len;
        }
        return single_len;
    }
};

int main()
{
    TreeNode tree = TreeNode(0);
    LongestPath path = LongestPath();
    int res = path.findPath(&tree);
    cout << res << endl;
}