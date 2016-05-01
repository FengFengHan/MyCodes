//
// Created by Han on 16/4/6.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define INF 10000000

using namespace std;

inline int MyCeil(int a, int b)
{
    int res;
    res = a/b + (a % b ? 1 : 0);
    return res;
}

int getPage(int word_w, vector<int>& nums, int w, int h)
{
   int line_w = w/word_w;
    int line_nums = 0;
    for(int i=0;i<nums.size();++i){
        line_nums += MyCeil(nums[i],line_w);
    }
    int p_numline = h/word_w;
    int res = MyCeil(line_nums,p_numline);
    return res;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int result =0;
    int T;
    scanf("%d",&T);
    for(int i=0;i < T;++i){
        int n,p,w,h;
        scanf("%d %d %d %d",&n,&p,&w,&h);
        vector<int> nums(n,0);
        int num;
        for(int j=0;j<n;++j){
            scanf("%d",&num);
            nums[j] = num;
        }
        int min_ = 1, max_ = w < h ? w : h;
        int start = min_;
        int end = max_;
        int mid,num_p;
        while(start < end){
            mid = (start + end)/2;
            if(mid == start){
                mid += 1;
            }
            num_p = getPage(mid, nums,w,h);
            if(num_p > p){
                end = mid - 1;
            }else if(num_p <= p){
                start = mid;
            }else{
                break;
            }
        }

        printf("%d\n",start);
    }
    return 0;
}
