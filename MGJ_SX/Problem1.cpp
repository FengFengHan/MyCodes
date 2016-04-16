//
// Created by Han on 16/3/31.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;


int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int n;
    while(scanf("%d",&n) != EOF){
        map<int, vector<int> > lens_cost;
        map<int, int> len_cost;
        vector<int> u_lens;
        vector<int> lens(n,0);
        vector<int> costs(n,0);
        map<int,int> counts;
        int tmp;
        for(int i=0;i < n;++i){
            scanf("%d",&tmp);
            lens[i] = tmp;
        }
        for(int i=0;i<n;++i){
            scanf("%d",&tmp);
            costs[i] = tmp;
        }
        int totalcost = 0;
        for(int i=0;i<n;++i){
            lens_cost[lens[i]].push_back(costs[i]);
            totalcost += costs[i];
        }
        int maxcost = 0;
        sort(lens.begin(),lens.end());
        u_lens.push_back(lens[0]);
        for(int i=1;i<lens.size();++i){
            if(lens[i] != lens[i-1]){
                u_lens.push_back(lens[i]);
            }
        }
        multiset<int> order_costs;
        for(int i=0;i<u_lens.size();++i){
            int sum_ = 0;
            vector<int> cur_costs = lens_cost[u_lens[i]];
            int num = cur_costs.size();
            for(int j=0;j<num;++j){
                sum_ += cur_costs[j];
            }
            int count = 0;
            for(multiset<int>::const_reverse_iterator iter = order_costs.rbegin();iter != order_costs.rend();++iter){
                int value = *iter;
                count += 1;
                if(count >= num){
                    break;
                }
                sum_ += value;
            }
            if(sum_ > maxcost){
                maxcost = sum_;
            }
            for(int j=0;j<num;++j){
                int value = cur_costs[j];
                order_costs.insert(value);
            }
        }
        int res;
        res = totalcost-maxcost;
        printf("%d\n",res);
    }

    return 0;
}
