#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

class Tree{
public:
    int val;
    Tree* left;
    Tree* right;
    Tree() : val(-1),left(NULL),right(NULL) {}
    Tree(int v){
        val = v;
        left = NULL;
        right = NULL;
    }
};

string int2string(int a)
{
    stringstream ss;
    ss << a;
    string res;
    res = ss.str();
    return res;
}

int string2int(string s)
{
    stringstream ss;
    ss << s;
    int res;
    ss >> res;
    return res;
}

void split_strtok(string str, string split_tokens, vector<string>& str_splits)
{
    char*  str_c = new char[str.size() + 10];
    strcpy(str_c,str.c_str());
    const char* split_tokens_c = split_tokens.c_str();
    char* str_split = strtok(str_c,split_tokens_c);
    while(str_split != NULL){
        str_splits.push_back(str_split);
        str_split = strtok(NULL,split_tokens_c);
    }
}

inline int MyCeil(int a, int b)
{
    int res;
    res = a/b + (a % b ? 1 : 0);
    return res;
}

void FillVector(istream& input, vector<int>& vec)
{
    int v;
    while(input >> v){
        vec.push_back(v);
    }
}

void BuildTree(vector<int>& vec)
{

}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    vector<int> numbers;
    FillVector(cin,numbers);
    return 0;
}