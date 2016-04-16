#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

void transfer(int num,string &s) {
    char tmp[8];
    int index=0;
    while(num!=0) {
        tmp[index++]=(num%2)+'0';
        num/=2;
    }
    int cnt=8-index;
    for(int i=0;i<cnt;i++)
        s+="0";
    for(int i=index-1;i>=0;i--)
        s+=tmp[i];
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int N,M;
    cin>>N>>M;
    string rules[N];
    string request;
    bool flag[N];
    string s;
    int num;
    char ch;
    int mask;
    for(int i=0;i<N;i++) {
        cin>>s;
        if(s.compare("allow")==0)
            flag[i]=true;
        else
            flag[i]=false;
        for(int j=0;j<4;j++) {
            scanf("%d",&num);
            transfer(num,rules[i]);
            scanf("%c",&ch);
        }
        if(ch=='/') {
            scanf("%d",&mask);
        }
        rules[i]=rules[i].substr(0,mask);

    }
    for(int i=0;i<M;i++) {
        request.clear();
        for(int j=0;j<4;j++) {
            scanf("%d",&num);
            transfer(num,request);
            scanf("%c",&ch);
        }
        bool isPrint=false;
        for(int k=0;k<N;k++) {
            bool isMatch=true;
            if(rules[k]!="") {
                for(size_t L=0;L<rules[k].size();L++) {
                    if(rules[k][L]!=request[L]) {
                        isMatch=false;
                        break;
                    }
                }
            }
            if(isMatch) {
                if(flag[k])
                    printf("YES\n");
                else
                    printf("NO\n");
                isPrint=true;
                break;
            }
        }
        if(!isPrint) {
            printf("YES\n");
        }
    }
    return 0;
}
