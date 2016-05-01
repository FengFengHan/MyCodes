#include <iostream>

using namespace std;

bool placed[105][105][105];

int MyMove[6][3] = {{1,0,0},
                  {-1,0,0},
                  {0,1,0},
                  {0,-1,0},
                  {0,0,1},
                  {0,0,-1}};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int T;
    scanf("%d",&T);
    for(int i=0;i<T;++i){
        int n;
        scanf("%d",&n);
        for(int d1=0;d1<105;++d1){
            for(int d2=0;d2<105;++d2){
                for(int d3=0;d3<105;++d3){
                    placed[d1][d2][d3] = false;
                }
            }
        }
        int x,y,z;
        bool able_place = true;
        for(int j=0; j<n;++j) {
            scanf("%d%d%d", &x,&y,&z);

            int x_n,y_n,z_n;
            int neibor_num = 0;
            if(able_place) {
                for(int k=0;k<6;++k){
                    x_n = x + MyMove[k][0];
                    y_n = y + MyMove[k][1];
                    z_n = z + MyMove[k][2];
                    if(x_n > 0 && x_n <= 100 && y_n> 0 && y_n <= 100 && z_n >=0 && z_n <= 100){
                        if(z_n == 0 || placed[x_n][y_n][z_n]){
                            neibor_num += 1;
                        }
                    }
                }
                if(neibor_num == 0 || neibor_num == 6){
                    able_place = false;
                }
            }

            placed[x][y][z] = true;
        }
        printf(able_place ? "YES\n" : "NO\n");

    }
}