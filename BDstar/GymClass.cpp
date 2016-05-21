#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <set>

//Gym Class

using namespace std;

typedef long long LL; ///!!!!!!!!!!
//typedef __int64 LL;

inline int MyCeil(int a, int b)
{
    int res;
    res = a/b + (a % b ? 1 : 0);
    return res;
}

int indegree[100010];
vector<int> after[100010];
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    int n,m;
    int A,B;
    for(int i=0; i < T;++i){
        LL score_sum = 0;
        scanf("%d %d",&n,&m);

        for(int j=1;j<=n;++j){
            indegree[j] = 0;
            after[j].clear();
        }

        for(int j=1;j<= m;++j){
            scanf("%d %d",&A, &B);
            after[A].push_back(B);
            indegree[B]++;
        }

        set<int> access_nums;
        for(int j=1;j<=n;++j){
            if(indegree[j] == 0){
                access_nums.insert(j);
            }
        }

        set<int>::reverse_iterator iter;
        int minval = 100010;
        while(access_nums.size()){
            iter = access_nums.rbegin();
            int val = *iter;
            if(val < minval){
                minval = val;
            }
            score_sum += minval;
            access_nums.erase(val);
            for(int k = 0; k< after[val].size();++k){
                int ele = after[val][k];
                indegree[ele]--;
                if(indegree[ele] == 0){
                    access_nums.insert(ele);
                }
            }
        }
        cout << score_sum << endl;
    }
    return 0;
}