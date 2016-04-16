//
// Created by Han on 16/3/10.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(string str1, string str2)////it is critical
{
    return (str1 + str2) < (str2 + str1);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    string res;
    vector<string> segments;
    int N;
    cin >> N;
    string segment;
    for(int i=0; i<N;++i){
        cin >> segment;
        segments.push_back(segment);
    }
    sort(segments.begin(),segments.end(),cmp);
    for(int i=0;i<N;++i){
        res += segments[i];
    }
    if(res[0] == '0'){
        cout << res.substr(1) << endl;
    }else{
        cout << res << endl;
    }
}