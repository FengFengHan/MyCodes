//
// Created by Han on 16/4/19.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>


using namespace std;


class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> res;
        int start = 0;
        int end = array.size() - 1;
        //Remove some invalid range
        while(start < end){
            int mid = (start + end)/2;
            if(array[start] + array[mid] > sum){
                end = mid - 1;
            }else if(array[mid] + array[end]<sum){
                start = mid  + 1;
            }else{
                break;
            }
        }
        //find valid solution
        long long min_product = -1;
        long long product;
        int v1, v2;
        while(start < end){
            if(array[start] + array[end] > sum){
                end -= 1;
            }else if(array[start] + array[end] < sum){
                start += 1;
            }else{
                product = array[start] * array[end];
                if(min_product < 0 || min_product > product){
                    min_product = product;
                    v1 = array[start];
                    v2 = array[end];
                }
                start += 1;
                end -= 1;
            }
        }
        if(min_product > 0) {
            res.push_back(v1);
            res.push_back(v2);
        }
        return res;
    }
};

int main()
{
    vector<int> array;
    array.push_back(3);
    array.push_back(4);
    int sum = 7;
    vector<int> res;
    Solution sol = Solution();
    res = sol.FindNumbersWithSum(array,sum);
    cout << res[0] << " " << res[1] << endl;
}