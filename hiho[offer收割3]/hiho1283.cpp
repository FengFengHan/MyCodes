//
// Created by Han on 16/3/27.
//
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> passwords;

int main() {
    int N;
    scanf("%d", &N);//写成带while循环的会出错
    passwords.clear();
    passwords.resize(N);
    int d;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &d);
        passwords[i] = d;
    }
    int num = N - 1;
    while ((num > 0) && (passwords[num] > passwords[num - 1])) {
        num--;
    }
    printf("%d", passwords[0]);
    for (int i = 1; i < num; ++i) {
        printf(" %d", passwords[i]);
    }
    printf("\n");
    return 0;
}