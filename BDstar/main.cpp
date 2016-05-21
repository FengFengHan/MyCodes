#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

typedef long long LL;
//typedef __int64 LL;

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

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif

    return 0;
}