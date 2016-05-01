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
class Partition {
public:
    vector<int> getPartition(const vector<vector<int> >& land, int n, int m) {
        // write code here
        vector<int> res;
        //
        vector<int> B(n,0);
        vector<int> A(n,0);
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                B[j] += land[i][j];
            }
        }
        for(int i=0;i<n;++i){
            A[i] = m - B[i];
        }
        //
        int right_sum = 0;
        for(int i=0;i<n;++i){
            right_sum += A[i];
        }
        int left_sum = 0;
        int min_sum = right_sum + left_sum;
        int split_point = 0;
        for(int i=0;i<n;++i){
            right_sum -= A[i];
            left_sum += B[i];
            if(right_sum + left_sum < min_sum){
                min_sum = right_sum + left_sum;
                split_point = i + 1;
            }
        }
        res.push_back(split_point);
        res.push_back(split_point + 1);
        return res;
    }
};

void FiilVector(int A[], vector< vector<int> >& vec, int n, int m)
{
    vec.resize(m);
    for(int i=0;i < m;++i){
        vec[i].resize(n);
        for(int j=0;j<n;++j){
            vec[i][j] = A[i*n + j];
        }
    }
}
int main()
{
    int n = 4, m = 3;
    vector<vector<int> > la;
    int A[12] = {1,1,1,1,0,0,0,0,1,0,1,1};
    FiilVector(A,la,n,m);
    Partition pa = Partition();
    vector<int> result = pa.getPartition(la,n,m);
     cout << result[0] << " " << result[1] << endl;
}