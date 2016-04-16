//
// Created by Han on 16/3/29.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int  solve_ori(int B, int b)
{
    int n;
    int start = 1;
    int end = B;
    int num_left, num_right;
    int b_left, b_right;
    b_left = b - 1;
    b_right = b + 1;
    num_left = b_left - start + 1;
    num_right = end - b_right + 1;

    n = num_right > num_left ? b_right : b_left;
    if (b_left < 1 && b_right <= B) {
        n = b_right;
    } else if (b_left >= 1 && b_right > B){
        n = b_left;
    }
    if(b_left < 1 && b_right > B){
        n = b;
    }
    return n;
}

int solve_new(int B, int b)
{
    if(B == 1){
        return 1;
    }
    int n;
    int mid = B/2 + B%1;
    if(b <= mid){
        n = b + 1;
    }else{
        n = b - 1;
    }
    return n;
}
int main()
{
    int B,b;
    while(scanf("%d %d",&B,&b) != EOF) {
        int n1 = solve_ori(B,b);
        int n2 = solve_new(B,b);
        if(n1 != n2){
            cout << "n1: " << n1 << " n2: " << n2 << endl;
        }
    }

}