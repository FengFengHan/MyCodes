//
// Created by Han on 16/4/15.
//

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

#define MYINF 100005

class TrieNode{
public:
    bool is_end;
    bool is_allow;
    int ind;
    TrieNode* next[2];
    TrieNode():is_end(false), is_allow(false),ind(MYINF) {
        next[0] = NULL;
        next[1] = NULL;
    }
};

void InsertTree(TrieNode* T,string str,int index,bool allow)
{
    if(str.size() == 0){
        T->is_end = true;
        if(index < T->ind){
            T->ind = index;
            T->is_allow=allow;
        }
        return;
    }
    int pos = 0;
    TrieNode** t_next;
    while(true){
        if(str[pos] == '0'){
            t_next = &(T->next[0]);
        }else{
            t_next = &(T->next[1]);
        }
        if(*t_next == NULL){
            *t_next = new TrieNode();
        }
        T = *t_next;
        if(pos == (str.size() - 1) ){
            if(index < T->ind) {//可能已经被标记过
                T->is_end = true;
                T->is_allow = allow;
                T->ind = index;
            }
            break;
        }
        pos++;
    }
}

bool SearchTree(string str,const TrieNode* T)
{
    bool res = true;
    int id = MYINF;
    int pos =0;
    while(T != NULL){
        if(T->is_end){
            if(T->ind <id) {
                id = T->ind;
                res = T->is_allow;
            }
        }
        if(str[pos] == '0'){
            T = T->next[0];
        }else{
            T = T->next[1];
        }
        pos++;
    }
    return res;
}

string GetIP(int* d,int mask_num = 32)
{
    string ip(32,'0');
    for(int i=0;i<4;++i){
        int pos = (i+1)*8-1;
        int num = d[i];
        while(num != 0){
            if(num % 2 == 1){
                ip[pos] = '1';
            }
            num = num / 2;
            pos--;
        }
    }
    ip = ip.substr(0,mask_num);
    return ip;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int n,m;
    scanf("%d%d",&n,&m);
    //read and insert tree
    TrieNode T = TrieNode();//faciliate to debug, than "TrieNode* T = new TriNode()"
    char s[10];
    int d[4];
    char c;
    for(int i=0;i<n;++i){
        scanf("%s%d.%d.%d.%d",s,d,d+1,d+2,d+3);
        scanf("%c",&c);
        int mask_num = 32;
        if(c == '/'){
            scanf("%d",&mask_num);
        }
        bool allow = (s[0] == 'a');
        string ip = GetIP(d,mask_num);
        InsertTree(&T,ip,i,allow);
    }
    //search tree
    for(int i=0; i<m;++i){
        scanf("%d.%d.%d.%d",d,d+1,d+2,d+3);
        string ip = GetIP(d);
        bool res = SearchTree(ip,&T);
        printf(res ? "YES\n" : "NO\n");
    }
}