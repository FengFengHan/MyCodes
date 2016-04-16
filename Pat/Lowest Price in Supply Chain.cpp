//
// Created by Han on 16/3/3.
//
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<vector<int> > Tree;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    //read
    int N;
    double price, r;
    scanf("%d %lf %lf", &N, &price, &r);
    Tree.resize(N);
    int distributor_num, distributor;
    for(int i =0; i < N; ++i){
        scanf("%d", &distributor_num);
        Tree[i].resize(distributor_num);
        for(int j=0; j < distributor_num; ++j){
            scanf("%d", &distributor);
            Tree[i][j] = distributor;
        }
    }
    //traverse by layer
    vector<int> cur_layer;
    vector<int> next_layer;
    int layer_num = 0;
    cur_layer.push_back(0);
    bool has_retailer = false;
    int retailer_num = 0;
    while(cur_layer.size() > 0){
        next_layer.clear();
        for(size_t i =0; i < cur_layer.size(); ++i){
            size_t distributor_id= cur_layer[i];
            if(Tree[distributor_id].begin() == Tree[distributor_id].end()){
                has_retailer = true;
                retailer_num += 1;
            }
            next_layer.insert(next_layer.end(),Tree[distributor_id].begin(),Tree[distributor_id].end());
        }
        if(has_retailer){
            break;
        }
        cur_layer = next_layer;
        layer_num += 1;
    }
    //get result
    double rate = pow((1 + r * 0.01),layer_num);
    double final_price = price * rate;
    printf("%.4f %d", final_price, retailer_num);

}
