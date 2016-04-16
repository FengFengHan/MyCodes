//
// Created by Han on 16/3/8.
//
#include <string>
#include <iostream>

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    string str;
    getline(cin,str);
    int max_len =0;
    for(int i =0;i<str.size();++i){
       int center = i,left, right;
        for(int j=1;j<3;++j) {
            left = center-1;
            if(j==2 && str[center] != str[center+1]){
                break;
            }
            right = center+j;
            int len = j;
            while (true) {
                if (left < 0 || right >= str.size()) {
                    break;
                }
                if (str[left] == str[right]) {
                    len += 2;
                }
                left -= 1;
                right += 1;
            }
            if (len > max_len) {
                max_len = len;
            }
        }
    }
    cout << max_len << endl;
}