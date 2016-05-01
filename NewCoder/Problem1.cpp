//
// Created by Han on 16/4/19.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

class Transform {
public:
    string trans(string s, int n) {
        // write code here
        vector<string> str_splits;
        //split_strtok(s," ",str_splits);
        string str;
        for(int i=0;i<n;++i){
            if(s[i] != ' ') {
                str += s[i];
            }else{
                str_splits.push_back(str);
                str = "";
            }
        }
        str_splits.push_back(str);
        string res;
        for(size_t i = str_splits.size() - 1;i > 0 ;--i){
            change(str_splits[i]);
            res += str_splits[i] + ' ';
        }
        change(str_splits[ 0]);
        res += str_splits[ 0];
        return res;
    }
    static void change(string& str){
        for(int i=0;i<str.size();++i){
            if('a' <= str[i] && str[i] <= 'z'){
                str[i] = 'A' + (str[i] - 'a');
            }else{
                str[i] = 'a' + (str[i] - 'A');
            }
        }
    }
    static void split_strtok(string str, string split_tokens, vector<string>& str_splits)
    {
        char*  str_c = new char[str.size() + 10];
        strcpy(str_c,str.c_str());
        const char* split_tokens_c = split_tokens.c_str();
        char* str_split = strtok(str_c,split_tokens_c);
        while(str_split != NULL){
            str_splits.push_back(str_split);
            str_split = strtok(NULL,split_tokens_c);
        }
    }
};

int main()
{
    string str = "Hello World";
    int n = 11;
    Transform t = Transform();
    string res = t.trans(str,n);
    cout << res << endl;
}