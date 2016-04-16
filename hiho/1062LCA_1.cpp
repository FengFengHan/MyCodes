//
// Created by Han on 16/4/14.
//

#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <set>

using namespace std;


map<string, vector<string> > Tree; //父母和孩子关系
map<string, vector<string> > Qes; //要查询的结点,用于深度优先搜索中
map<pair<string, string>, string> lca; //查询到的信息
map<string, string> ancestror; //结点的祖先
vector< pair<string, string> > RQes; //要查询的结点,用于输出答案
set<string> not_root; //用于查找根结点

string FindRoot(string name)//并查集
{
    if(ancestror[name] == "-1"){
        return name;
    }
    string root = FindRoot(ancestror[name]);
    ancestror[name] = root;
    return root;
}

void Dfs(string father, set<string>& visited)
{

    const vector<string>& sons = Tree[father];
    for(int i=0; i < sons.size();++i){
        string son = sons[i];
        Dfs(son,visited);
        ancestror[son] = father;//指向father
    }

    visited.insert(father);

    if(Qes.count(father)){
        string q;
        for(int i=0;i< Qes[father].size();++i){
            q= Qes[father][i];
            if(visited.count(q)){
                string root = FindRoot(q);
                lca[make_pair(father,q)] = root;
                lca[make_pair(q,father)] = root;
            }
        }
    }

}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int n;
    cin >> n;
    string father,son;
    for(int i=0;i<n;++i){
        cin >> father >> son;
        Tree[father].push_back(son);
        not_root.insert(son);
        ancestror[father] = "-1";
        ancestror[son] = "-1";
    }

    int m;
    cin >> m;
    string q1,q2;
    for(int i=0;i<m;++i){
        cin >> q1 >> q2;
        Qes[q1].push_back(q2);
        Qes[q2].push_back(q1);
        RQes.push_back(make_pair(q1,q2));
    }

    for(map<string,vector<string> > ::const_iterator iter = Tree.begin();iter != Tree.end();++iter){
        if(not_root.count(iter->first)){
            continue;
        }else {//根结点
            set<string> visited;
            Dfs(iter->first,visited);
        }
    }

    for(size_t i=0;i< m;++i){
        if(lca.find(RQes[i]) != lca.end()){//查询到
            cout << lca[RQes[i]] << endl;
        }else{
            cout << "-1" << endl;
        }
    }
}