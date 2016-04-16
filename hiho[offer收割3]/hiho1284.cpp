//
// Created by Han on 16/3/27.
//

#include <iostream>
#include <unordered_set>

using namespace std;

unordered_set<long long> reducts_N;
unordered_set<long long> reducts_M;

long long reductN(long long a) {
    long long res = 1;
    long long start = 2;
    if (a % 2 == 1) {
        start = 3;
    }
    for (long long i = start; i <= a; i += 2) {
        if (a % i == 0) {
            res += 1;
        }
    }
    return res;
}

void GetReducts(long long a, unordered_set<long long>& reducts)
{
    for(long long i=1;i * i <= a;++i){
        if(a % i == 0) {
            reducts.insert(i);
            reducts.insert(a / i);
        }
    }
}

long long gcd(long long a, long long b) {
    if (a < b) {
        long long tmp = a;
        a = b;
        b = tmp;
    }
    long long c;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}


int main() {
    long long N, M;
    cin >> N >> M;
    if(N  < M){
        long long tmp = N;
        N = M;
        M = tmp;
    }
    //test
//    while(!cin.eof()) {
//        cin >> N >> M;
//        long long N_rnum = reductN(N);
//
//        long long M_rnum = reductN(M);
//        long long gcd_ = gcd(N, M);
//
//        long long gcd_rnum = reductN(gcd_);
//        cout << "N_rnum" << N_rnum << endl;
//        cout << "M_rnum" << M_rnum << endl;
//        cout << "gcd" << gcd_ << endl;
//        cout << "gcd_rnum" << gcd_rnum;
//        long long same_num = gcd_rnum;
//        long long total_num = M_rnum * N_rnum;
//        long long res_gcd = gcd(total_num, same_num);
//        cout << (total_num / res_gcd) << " " << (same_num / res_gcd) << endl;
//    }
    GetReducts(N,reducts_N);
    GetReducts(M,reducts_M);
    long long numN = reducts_N.size();
    long long numM = reducts_M.size();
    long long total_num = numM * numN;//直接写成:reducts_N.size() * reducts_M.size()会出错
    long long same_num = 0;
    for(unordered_set<long long>::const_iterator iter = reducts_M.begin();iter != reducts_M.end();++iter){
        if(reducts_N.count(*iter)){
            same_num += 1;
        }
    }
    long long res_gcd = gcd(total_num, same_num);
    cout << (total_num / res_gcd) << " " << (same_num / res_gcd) << endl;
    return 0;
}