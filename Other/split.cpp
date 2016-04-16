//
// Created by Han on 16/4/15.
//
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cstring>

using std::string;
using std::vector;
using std::cout;
using std::endl;

void split_boost(string str, string split_tokens, vector<string>& str_splits)
{
    boost::split(str_splits,str,boost::is_any_of(split_tokens));
}

void split_strtok(string str, string split_tokens, vector<string>& str_splits)
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

void split_strfind(string str, string split_tokens, vector<string>& str_splits)
{
    string str_split;
    size_t pos1 = 0;
    size_t pos2 = 0;
    while(pos2 != string::npos) {
        pos1 = str.find_first_not_of(split_tokens,pos2);
        if(pos1  == string::npos){
            break;
        }
        pos2 = str.find_first_of(split_tokens,pos1);
        if(pos2 == string::npos){
            str_split = str.substr(pos1);
        }else{
            str_split = str.substr(pos1,pos2-pos1);
        }
        str_splits.push_back(str_split);
    }
}
int main()
{
    char split_tokens[5] = "#.-,";

    //1. boost
    string str = "-#This,#a#sample#string.";
    vector<string> split_strs;
    split_boost(str,split_tokens,split_strs);
    cout << "1: boost" << endl;
    for(size_t i =0;i<split_strs.size();++i){
        cout << split_strs[i] << endl;
    }
    //2. strtok
    string str2 = "-This,#a#sample#string.";
    vector<string> split_strs2;
    split_strtok(str2,split_tokens,split_strs2);
    cout << "2: strtok"  << endl;
    for(size_t i=0;i<split_strs2.size();++i){
        cout << split_strs2[i] << endl;
    }

    //3. string find
    string str3 = "-This,#a#sample#string.";
    vector<string> split_strs3;
    split_strfind(str3,split_tokens,split_strs3);
    cout << "3: str find" << endl;
    for(size_t i=0;i<split_strs3.size();++i){
        cout << split_strs3[i] << endl;
    }
}


