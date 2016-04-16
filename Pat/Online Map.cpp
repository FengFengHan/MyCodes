#include <vector>//
// Created by Han on 16/3/13.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const int myINF = 100000000;

class Road{
public:
    int length_;
    int time_;
    Road(): length_(myINF), time_(myINF) {}
    Road(int len, int t){
        length_ = len;
        time_ = t;
    }
};

class Path{
public:
    vector<int> nodes_;
    Road road_;
    Path(){
        road_ = Road(myINF, myINF);
    }
    Path(vector<int> nodes, Road road){
        nodes_ = nodes;
        road_ = road;
    }

};

bool operator==(const Path& path1, const Path& path2)
{
    return(path1.nodes_ == path2.nodes_ && path1.road_.time_ == path2.road_.time_ &&
    path1.road_.length_ == path2.road_.length_);
}

bool cmp_len(const Path& path1, const Path& path2)
{
    if(path1.road_.length_ != path2.road_.length_){
        return path1.road_.length_ < path2.road_.length_;
    }else{
        return path1.road_.time_ < path2.road_.time_;
    }
}

bool cmp_time(const Path& path1, const Path& path2)
{
    if(path1.road_.time_ != path2.road_.time_){
        return path1.road_.time_ < path2.road_.time_;
    }else{
        return path1.nodes_.size() < path2.nodes_.size();
    }
}

vector< vector<int> > intersections;
Road roads[501][501];


Path Dijstla(int s, int d, vector< vector<int> > connects, Road roads[][501], bool (*cmp)(const Path&, const Path&))
{
    unsigned  int N = connects.size();
    vector<bool> visited(N,false);
    vector<Path> P(N);
    visited[s] = true;
    for(int i=0;i < connects[s].size();++i){
        int intersection = connects[s][i];
        P[intersection].nodes_.push_back(s);
        P[intersection].nodes_.push_back(intersection);
        P[intersection].road_ = roads[s][intersection];
    }
    for(int i =0;i<N;++i){
        //select min path
        int sel = -1;
        Path min = Path();
        for(int j=0;j<N;++j){
            if(!visited[j]){
                if(cmp(P[j],min)){
                    min = P[j];
                    sel = j;
                }
            }
        }
        if(sel == -1){
            cout << "no select " << endl;
        }
        visited[sel] = true;
        if(sel == d){
            break;
        }
        //update path by sel
        for(int j=0;j<connects[sel].size();++j){
            int inter = connects[sel][j];
            Path path_new = P[sel];
            path_new.road_.length_ += roads[sel][inter].length_;
            path_new.road_.time_ += roads[sel][inter].time_;
            path_new.nodes_.push_back(inter);
            if(cmp(path_new,P[inter])){
                P[inter] = path_new;
            }
        }

    }
    return P[d];

}

string GetSquence(vector<int> numbers)
{
    ostringstream ss;
    ss << numbers[0];
    for(int i= 1;i <numbers.size();++i){
        //res += " -> " + numbers[i];
        ss <<  " -> ";
        ss << numbers[i];
    }
    return ss.str();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    int N,M;
    cin >> N >> M;
    intersections.resize(N);
    int v1, v2, one_way, len,time_;
    for(int i=0;i<M;++i){
        cin >> v1 >> v2 >> one_way >> len >> time_;
        intersections[v1].push_back(v2);
        roads[v1][v2] = Road(len,time_);
        if(one_way == 0){
            intersections[v2].push_back(v1);
            roads[v2][v1] = roads[v1][v2];
        }
    }
    int s,d;
    cin >> s >> d;
    Path shortest = Dijstla(s,d,intersections,roads,cmp_len);
    Path fastest = Dijstla(s,d,intersections,roads,cmp_time);
    if(shortest == fastest){
        printf("Distance = %d; Time = %d: %s\n",shortest.road_.length_, shortest.road_.time_,
               (GetSquence(shortest.nodes_)).c_str());
    }else{
        printf("Distance = %d: %s\n",shortest.road_.length_,
               (GetSquence(shortest.nodes_)).c_str());
        printf("Time = %d: %s\n",fastest.road_.time_,
               (GetSquence(fastest.nodes_)).c_str());
    }
}
