//
// Created by Han on 16/4/6.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <queue>

using namespace std;

typedef long long LL;
//typedef __int64 LL;

string int2string(int a)
{
    stringstream ss;
    ss << a;
    string res;
    res = ss.str();
    return res;
}

int string2int(string s)
{
    stringstream ss;
    ss << s;
    int res;
    ss >> res;
    return res;
}




int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    for(int i=0; i< T;++i){
        map<int,vector<int> > sig_sigs;
        queue<int> sigs;
        map<int,vector<int> > sig_mas;

        int n,m;
        scanf("%d %d",&n,&m);
        vector<int> Count(n,0);

        for(int j=0;j<m;++j){
            int sig;
            scanf("%d",&sig);
            sigs.push(sig);
        }

        for(int j=0;j<n;++j){
            int sta_sig;
            int sig_cnt;
            scanf("%d %d",&sta_sig,&sig_cnt);
            sig_mas[sta_sig].push_back(j);
            int gen_sig;
            for(int k=0;k<sig_cnt;++k){
                scanf("%d",&gen_sig);
                sig_sigs[sta_sig].push_back(gen_sig);
            }
            Count[j] = 0;
        }

        int sig;
        while(!sigs.empty()){
            sig = sigs.front();
            sigs.pop();

            vector<int>& mas = sig_mas[sig];
            for(int i=0;i< mas.size();++i){
                Count[mas[i]] += 1;
                if(Count[mas[i]] > 142857){
                    Count[mas[i]] %= 142857;
                }
            }

            vector<int>& gen_sigs = sig_sigs[sig];
            for(int i=0;i<gen_sigs.size();++i){
                sigs.push(gen_sigs[i]);
            }

        }

        printf("%d", Count[0]);
        for(int i=1;i<n;++i){
            printf(" %d",Count[i]);
        }
        printf("\n");
    }
    return 0;
}
