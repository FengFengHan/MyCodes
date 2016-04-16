//
// Created by Han on 16/3/8.
//
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    string str;
    getline(cin,str);
    int n = str.size();
    string str_new(2 * n + 1,'e');
    str_new[0] = '#';
    for(size_t i= 0; i< str.size();++i){
       str_new[2*i +1] = str[i];
        str_new[2*i + 2] = '#';
    }
    vector<int> lens(str_new.size(),1);
    int num = str_new.size();
    int max_len;
    int max_pos;
    int max_index = -1;
    for(int i=0;i<num;++i){
        int len = 1;
       if(i < max_index){
           len =  min(lens[2*max_pos - i],max_index-i+1);
       }
        while(i-len >=0 && i+len < num &&
            (str_new[i-len] == str_new[i+len])) {
            len += 1;
        }
        lens[i] = len;
        if(len >max_len){
            max_len = len;
        }
        if(i+len-1 > max_index){
            max_index = i + len -1;
            max_pos = i;
        }
    }
    cout << max_len -1 << endl;
}