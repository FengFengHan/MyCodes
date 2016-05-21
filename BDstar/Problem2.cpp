#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

//Sitting in Line

using namespace std;

typedef long long LL;
//typedef __int64 LL;


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