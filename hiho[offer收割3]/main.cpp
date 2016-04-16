#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int a,b;
    int sum_;
    while(scanf("%d", &a) != EOF){
        scanf("%d",&b);
        sum_ = a+b;
        printf("%d\n",sum_);
    }
    return 0;
}