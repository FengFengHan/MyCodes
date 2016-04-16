#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

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

int main() {
#ifndef ONLINE_JUDGE
    //freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    unsigned long long ip =  219142053100;
    unsigned long long temp = ip >> 32;
    cout << temp << endl;
    return 0;
}