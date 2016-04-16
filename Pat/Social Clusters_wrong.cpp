//
//  Social Clusters.cpp
//  Pat
//
//  Created by Han on 16/3/1.
//  Copyright © 2016年 Han. All rights reserved.
//
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <fstream>
using namespace std;

bool comp(int a, int b){
   return a > b;
}

// for example
//3
//2: 2 7
//1: 3
//2: 3 2
//has wrong
int main()
{
#ifndef ONLINE_JUDGE
//    ifstream filestr;
//    filestr.open("/Users/HAN/Documents/Pat/in.txt");
//    streambuf* backup;
//    backup = cin.rdbuf();
//    cin.rdbuf(filestr.rdbuf());
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    int N;
    scanf("%d", &N);
    const int K = 1001;
    vector<bitset<K> > Clusters;
    Clusters.resize(N);
    //input
    int k;
    int h;
    for(int i = 0;i<N;++i){
        scanf("%d:", &k);
        for(int j = 0; j < k; ++j){
            scanf("%d",&h);
            Clusters[i].set(h);
        }
    }
    //count
    vector<int> cluster_sizes;
    cluster_sizes.resize(N);
    for(int i = 0; i < N;++i){
       cluster_sizes[i] = 1;
    }
    //merge and count
    int clusters_num = N;
    bitset<K> cluster;
    for(int i = 0; i < clusters_num;++i){
        //find same and move to the last:
        int j = 0;
        while (j < clusters_num) {
            if(j != i) {
                cluster = Clusters[i] & Clusters[j];
                if (cluster.any()) {
                    Clusters[i] = Clusters[i] | Clusters[j];
                    cluster_sizes[i] += cluster_sizes[j];
                    if(j != clusters_num -1 && i != clusters_num -1) {
                        Clusters[j] = Clusters[clusters_num - 1];
                        cluster_sizes[j] = cluster_sizes[clusters_num - 1];
                        j -= 1;
                    }
                    cluster_sizes[clusters_num-1] = 0;
                    clusters_num -= 1;
                }
            }
            j += 1;
        }
    }
    cout << clusters_num << endl;
    sort(cluster_sizes.begin(), cluster_sizes.end(),comp);
    cout << cluster_sizes[0];
    for(int i = 1; i < clusters_num;++i){
        cout << " " << cluster_sizes[i];
    }
    cout << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif
}
