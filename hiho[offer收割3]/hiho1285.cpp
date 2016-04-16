//
// Created by Han on 16/3/27.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

int N, M, S, T;
vector<int> scores;

bool calculated[1010][1010];
int right_nums[1010][1010];

int GetNum(int score, int unit_)
{
    if(score < 0){
        return 0;
    }
    int res = score/unit_;
    if(res*unit_ < score){
        res += 1;
    }
    return res;
}
int MinRight(int a, int q_num)
{
    int res = -1;
    if(a == N){
        return 0;
    }
    int score = scores[a];
    int max_rightN = GetNum(score,S);
    if(q_num < max_rightN){
        return res;
    }
    for(int rightN = 0; rightN <= max_rightN;++rightN){
        int wrongN = GetNum(score - rightN*S,T);
        int usedN = rightN + wrongN;
        if(usedN <= q_num){
            int next_a = a+1;
            int next_q_num = q_num-usedN;
            if(!calculated[next_a][next_q_num]) {
                right_nums[next_a][next_q_num] = MinRight(next_a,next_q_num);
                calculated[next_a][next_q_num] = true;
            }
            int sub_rightN = right_nums[next_a][next_q_num];
            if(sub_rightN >= 0){
                int tmpRes = rightN + sub_rightN;
                if(res == -1){
                    res = tmpRes;
                } else if(tmpRes < res){
                    res = tmpRes;
                }
            }
        }
    }
    return res;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> N >> M >> S >> T;
        for(int j=0;j<=N;++j){
            for(int k=0;k<= M;++k){
                calculated[j][k] = false;
            }
        }
        scores.clear();
        int score;
        for (int j = 0; j < N; ++j) {
            cin >> score;
            scores.push_back(score);
        }

        int res = MinRight(0, M);
        if (res < 0) {
            cout << "No" << endl;
        } else {
            cout << res << endl;
        }
    }
}
