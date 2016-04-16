#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

typedef unsigned int ULL;
//typedef __int64 LL;

#define w1 24
#define w2 16
#define w3 8


struct IP{
    bool valid_;
    bitset<16> ip_;
    int mask_;

    IP():valid_(-1), mask_(-1){}
    IP(bool valid, bitset<16> ip, int mask){
        valid_ = valid;
        ip_ = ip;
        mask_ = mask;
    }

};

IP IPs[100010];

inline int string2int(string s)
{
    stringstream ss;
    ss << s;
    int res;
    ss >> res;
    return res;
}


void process(string str,int id)
{
    bool valid = false;
    bitset<16> ip;
    int mask = 32;

    if(str[0] == 'a'){
        valid = true;
    }

    int pos = str.find(" ");
    int pos2 = str.find("/");
    string ip_ad = str.substr(pos+1,pos2-pos);
    ip.reset();
    ULL d1,d2,d3,d4;
    sscanf(ip_ad.c_str(),"%u.%u.%u.%u",&d1,&d2,&d3,&d4);


    if(pos2 < str.size()){
        string mask_str = str.substr(pos2 + 1);
        sscanf(mask_str.c_str(),"%d",&mask);
    }

    IPs[id] = IP(valid, ip, mask);
}

int match(ULL ip,int n) {
    int mask;
    for (int i = 0; i < n; ++i) {
            mask = 32 - IPs[i].mask_;
            if(ip >> mask == (IPs[i].ip_ )>> mask){
                return i;
            }
    }
    return -1;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int N,M;
    cin >> N >> M;
    string str;
    getline(cin,str);
    for(int i=0;i<N;++i){
        getline(cin,str);
        process(str,i);
    }
    for(int i=0;i<M;++i){
        ULL d1,d2,d3,d4;
        scanf("%u.%u.%u.%u",&d1,&d2,&d3,&d4);
        ULL ip = (w1 << d1) + (w2 << d2) +  (w3<<  d3) + d4;
        int res = match(ip,N);
        if(res == -1){
            printf("YES\n");
        }else{
            printf(IPs[res].valid_ ? "YES\n" : "NO\n");
        }
    }
    return 0;
}