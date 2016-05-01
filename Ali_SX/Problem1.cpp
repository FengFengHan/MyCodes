//
// Created by Han on 16/4/20.
//
#include <iostream>

using namespace std;

int main()
{
    long long a = 1;
    long long b = 1;
    int n= 54, m = 27;
    for(int i=0;i<m;++i){
        a *= (n-i);
    }
    for(int i=m;i>0;--i){
        b *= i;
    }
    cout << a <<" " <<  b << " " << a/b;
 }
