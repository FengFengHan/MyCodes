//
// Created by Han on 16/3/31.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int d1, d2, d3, d4;
    while(scanf("%d %d %d %d",&d1, &d2, &d3, &d4) != EOF){
        if(d1 +d2 + d3 + d4 != 10){
            printf("%d\n", -1);
        }
        printf("%d\n",4);
    }

    return 0;
}
