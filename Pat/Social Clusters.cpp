//
// Created by Han on 16/3/2.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int x, int y)
{
    return x >y;
}
const int K = 1001;
int trees[K];
int num[K];

int FindRoot(int node)
{
    if(trees[node] == 0){
        return node;
    }
    trees[node] = FindRoot(trees[node]);
    return trees[node];
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt", "r", stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt", "w", stdout);
#endif
    int N;
    scanf("%d", &N);
    for(int i=0; i < N;++i){
       int k;
        scanf("%d:",&k);
        int h;
        scanf("%d",&h);
        int root = FindRoot(h);
        num[root] += 1;
        int root_tmp;
        for(int j= 1; j < k;++j){
            scanf("%d",&h);
            root_tmp = FindRoot(h);
            if(root_tmp != root){
                trees[root_tmp] = root;
                num[root] += num[root_tmp];
            }
        }
    }

    vector<int> cluster_nums;
    int root;
    for(int i=1;i<K;++i){
          root = FindRoot(i);
        if(root == i and num[root] > 0){
            cluster_nums.push_back(num[root]);
        }
    }
    sort(cluster_nums.begin(),cluster_nums.end(),cmp);
    cout << cluster_nums.size() << endl;
    cout << cluster_nums[0];
    for(int i=1;i<cluster_nums.size();++i){
        cout << " " << cluster_nums[i];
    }
    cout << endl;
#ifndef ONLINE_JUDGE
    fclose(stdin);
    fclose(stdout);
#endif
}
