#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef long long LL;
//typedef __int64 LL;

#define myINF 1000000

int main() {
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int n,m;
    cin >> n >> m;
    int steps[n][m][2];//row, col, right an down
    //vector< vector<int> > steps(n, vector<int>(m));
    string str;
    getline(cin,str);
    vector<string> mazes(n);
    for(int i=0;i<n;++i){
        getline(cin, mazes[i]);
    }

    steps[n-1][m-1][0] = 0;//right
    steps[n-1][m-1][1] = 0;//down

    //last row
    for(int i=m-2;i >= 0; --i){
        steps[n-1][i][0] = steps[n-1][i+1][0];
        if(mazes[n-1][i+1] == 'b'){
             steps[n-1][i][0] += 1;
        }

        steps[n-1][i][1] = myINF;
    }

    //last col
    for(int i= n-2;i>=0;--i){
        steps[i][m-1][0] = myINF;

        steps[i][m-1][1] = steps[i+1][m-1][1];
        if(mazes[i+1][m-1] == 'b'){
            steps[i][m-1][1] += 1;
        }
    }

    int right,down;
    for(int i = n-2;i>=0;--i){
        for(int j=m-2;j>=0;--j){
            int right_right = steps[i][j+1][0];
            int right_down = steps[i][j+1][1];
            if(j+1 < m-1 && mazes[i][j+2] != 'b'){
                right_down += 1;
            }
            right = right_right < right_down ? right_right : right_down;
            if(mazes[i][j+1] == 'b'){
                right += 1;
            }
            steps[i][j][0] = right;

            int down_right = steps[i+1][j][0];
            if(i+1 < n-1 && mazes[i+2][j] != 'b'){
                down_right += 1;
            }
            int down_down = steps[i+1][j][1];
            down = down_right < down_down ? down_right : down_down;
            if(mazes[i+1][j] == 'b'){
                down += 1;
            }
            steps[i][j][1] = down;

        }
    }

    if(m > 1){
        if(mazes[0][1] != 'b'){
            steps[0][0][1] += 1;
        }
    }
    int res = steps[0][0][0] < steps[0][0][1] ? steps[0][0][0] : steps[0][0][1];
    if(mazes[0][0] == 'b'){
        res += 1;
    }
    printf("%d\n",res);
    return 0;
}