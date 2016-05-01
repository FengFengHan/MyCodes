//
// Created by Han on 16/4/21.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;
typedef unsigned  long long ULL;

string int2string(ULL a)
{
    stringstream ss;
    ss << a;
    string res;
    res = ss.str();
    return res;
}

ULL string2int(string s)
{
    stringstream ss;
    ss << s;
    ULL res;
    ss >> res;
    return res;
}

char help[] = {'1','2','3','4','5','6','7','8','9'};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    ULL a;
    ULL b;
    while(cin >> a){
        cin >> b;
        string a_str = int2string(a);
        string b_str = int2string(b);
        size_t a_count = a_str.size();
        size_t b_count = b_str.size();

        if(a_count <= b_count){
            a_str = b_str;
        }else {
            size_t i=0;
            size_t j= 0;
            size_t next_pos = 0;
            for (; i < b_count; ++i) {
                char tmp = b_str[i];
                j = a_str.find(tmp, next_pos);
                if (j == string::npos || (a_count - j < b_count - i)) {
                    break;
                }
                next_pos = j+1;
            }
            size_t b_pos = b_count - 1;
            size_t a_pos = a_count - 1;
            while(b_pos >= i){
                a_str[a_pos] = b_str[b_pos];
                a_pos--;
                if(b_pos == 0){
                    break;
                }
                b_pos--;

            }
        }

        ULL new_a = string2int(a_str);
        if(new_a > a){
            cout << a_str << endl;
        }else{
            bool find_ = false;
            for(int i=a_str.size()-1;i >=0;--i){
                if(a_str[i] != '4' && a_str[i] != '7' && a_str[i] < '9'){
                    find_ = true;
                    a_str[i] = help[a_str[i] - '0'];
                    break;
                }
            }
            if(!find_){
                a_str = string("1") + a_str;
            }
            cout << a_str << endl;
        }
    }
}
