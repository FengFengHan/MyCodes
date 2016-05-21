#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

//BD string

using namespace std;

typedef unsigned long long LL;
//typedef __int64 LL;

LL get_b_num(LL bnd){
    LL count = 0;
   if(bnd == 0){
       return 0;
   }
   LL format_num = 1;
   while(format_num < bnd){
       format_num = format_num * 2 + 1;
   }
    LL left_format_num = format_num/2;
    LL left_format_count = left_format_num /2 ;
    count += left_format_count;
    count += 1;
    LL remain_num = bnd - left_format_num -1;
    LL remain_count = remain_num - (left_format_count - get_b_num(left_format_num - remain_num));
    count += remain_count;
    return count;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int t;
    LL l, r;
    cin >> t;
    for(int i=0; i <t;++i){
        cin >> l >> r;
        LL num2 = get_b_num(r);
        LL num1 = get_b_num(l-1);
        cout << num2 - num1 << endl;
    }
    return 0;
}