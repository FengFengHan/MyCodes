//
// Created by Han on 16/4/5.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

#define INF 10000
#define MAXN 100100

struct Edge{
    int vex;
    int w;
    struct Edge* next;
    Edge():vex(-1),w(-1),next(NULL) {}
    Edge(int id, int weight){
        vex = id;
        w = weight;
    }
};

struct Node{
    Edge* first_;
};

struct Dot{
    int s;
    int t;
    Dot():s(-1),t(-1) {}
    Dot(int start,int end){
        s= start;
        t = end;
    }

};

bool operator<(const Dot& dot1, const Dot& dot2){
    if(dot1.s != dot2.s){
        return dot1.s < dot2.s;
    }else{
        return dot1.t < dot2.t;
    }
}


map<Dot,int> infos;

vector<int> dis(MAXN,INF);
vector<int> heap(MAXN);// nodes id
vector<int> pos(MAXN);//nodes id to heap pos

void addEdges(int start,int end,int weight,vector<Node>& nodes)
{

    Edge* tmp = nodes[start].first_;
    nodes[start].first_ = new Edge(end, weight);
    nodes[start].first_->next = tmp;

    tmp = nodes[end].first_;
    nodes[end].first_ = new Edge(start, weight);
    nodes[end].first_->next =  tmp;

}

void swap_(int pos1, int pos2)
{
    int tmp = heap[pos1];
    heap[pos1] = heap[pos2];
    heap[pos2] = tmp;
    //update pos
    pos[heap[pos1]] = pos1;
    pos[heap[pos2]] = pos2;
}


void HeapUp(int pos_node,int end)
{
    int pos_parent = (pos_node-1)/2;
    while(pos_node > 0){
        if(dis[heap[pos_node]] < dis[heap[pos_parent]]){
            swap_(pos_node,pos_parent);
        }else{
            break;
        }
        pos_node = pos_parent;
        pos_parent = (pos_node-1)/2;
    }

}


void HeapDown(int pos_node, int end)
{
    for(int i = pos_node*2 + 1; i < end; i = i*2 + 1)
    {
        if(i + 1 < end){
            if(dis[heap[i+1]] < dis[heap[i]]){
                ++i;
            }
        }
        if(heap[pos_node] > heap[i]){
            swap_(pos_node,i);
        }else{
            break;
        }
    }
}


int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    int ans = 0;
    int n,m;
    scanf("%d %d",&n, &m);
    vector<Node> nodes(n+10);
    int v1, v2, w;
    for(int i =0;i<m;++i){
        scanf("%d %d %d",&v1,&v2,&w);
        if(v1 > v2){
            int tmp = v1;
            v1 = v2;
            v2 = tmp;
        }
        if(infos.find(Dot(v1,v2)) == infos.end()) {
            infos[Dot(v1, v2)] = w;
        }else{
            if(w < infos[Dot(v1,v2)]){
                infos[Dot(v1,v2)] = w;
            }
        }
    }

    for(map<Dot,int>::const_iterator iter = infos.begin();iter != infos.end();++iter){
        v1 = (iter->first).s;
        v2 = (iter->first).t;
        w = iter->second;
        addEdges(v1,v2,w,nodes);
    }

    int count = 0;
    for(int i=1;i<=n;++i){
        heap[count] = i;
        pos[i] = count;
        count++;
    }

    int sel_num = 0;
    int sel;
    while(sel_num < n){
        sel = heap[0];
        sel_num++;
        if(sel_num > 1){
            ans += dis[sel];
        }
        pos[sel] = -1;
        heap[0] = heap[count -1];
        pos[heap[0]] = 0;
        count -= 1;
        HeapDown(0,count);
        Edge* edge = nodes[sel].first_;
        while(edge != NULL){
            int node_vex = edge->vex;
            if(pos[node_vex] != -1){
                if(dis[node_vex] > edge->w){
                    dis[node_vex] = edge->w;
                }
                int pos_node = pos[node_vex];
                HeapUp(pos_node,count);
                HeapDown(pos_node,count);
            }
            edge = edge->next;
        }
    }
    printf("%d\n",ans);
}
