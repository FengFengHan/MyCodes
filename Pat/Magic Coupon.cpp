//
// Created by Han on 16/3/10.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> cp; //coupon for positive
vector<int> cn; //coupon for negtive
vector<int> pp; //product for positive
vector<int> pn;

bool cmp(int v1, int v2){
    return  v1 > v2;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    int nc, np;
    cin >> nc;
    int value;
    for(int i=0; i < nc;++i){
        cin >> value;
        if(value >=0){
            cp.push_back(value);
        }else{
            cn.push_back(-1*value);
        }
    }
    cin >> np;
    for(int i=0; i< np;++i){
        cin >>value;
        if(value >= 0){
            pp.push_back(value);
        }else{
            pn.push_back(-1*value);
        }
    }
    //sort: from big to small
    sort(cp.begin(),cp.end(),cmp);
    sort(cn.begin(),cn.end(),cmp);
    sort(pp.begin(),pp.end(),cmp);
    sort(pn.begin(),pn.end(),cmp);
    int total = 0;
    //coupon and product both are positive
    int positive_num = (cp.size() < pp.size() ? cp.size() : pp.size());
    for(int i=0; i < positive_num;++i){
        total += cp[i]*pp[i];
    }
    //coupon and product both are negative
    int neg_num = (cn.size() < pn.size() ? cn.size() : pn.size());
    for(int i=0; i<neg_num;++i){
        total += cn[i]*pn[i];
    }
    cout << total << endl;
}

