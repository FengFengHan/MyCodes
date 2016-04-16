//
// Created by Han on 16/3/29.
//
//
// Created by Han on 16/3/29.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

char s[300010];

int GetP(char* str)
{
    int res = 0;
    int len = strlen(str);
    int i=0;
    while(i < len){
        if(str[i] == '.'){
            int num = 0;
            ++i;
            while(i < len && str[i] == '.'){
                num += 1;
                ++i;
            }
            res += num;
        }
        ++i;
    }
    return res;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int n,m;
    while(scanf("%d %d",&n,&m) != EOF){
        char temp[2];
        gets(temp);
        gets(s);
        int pos;
        char c,ori;
        int num = GetP(s);
        for(int i=0;i<m;++i){
            scanf("%d",&pos);
            scanf("%c",&c);
            scanf("%c",&c);
            pos -= 1;
            ori = s[pos];
            s[pos] = c;
            if(ori != '.' && c != '.'){
                printf("%d\n",num);
            }else{
                num = GetP(s);
                printf("%d\n",num);
            }
        }

    }
    return 0;


}
