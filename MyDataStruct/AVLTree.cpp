//
// Created by Han on 16/3/25.
//

#include <cstdio>

using namespace std;

int main()
{
    const int LIMIT = 1000000000;
    int nodes[1000];
    nodes[0] = 1;
    nodes[1] = 2;
    for(int i = 3;i<1000;++i){
        nodes[i] = nodes[i-2] + nodes[i-1] + 1;
        if(nodes[i] > LIMIT){
            break;
        }
    }
    int n;
    while(scanf("%d",&n) != EOF){
        if(n == 0){
            break;
        }
        int h = 0;
        while(nodes[h] <= n){
            h++;
        }
        --h;
        printf("%d\n",h);
    }
}
