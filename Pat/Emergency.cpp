#include <iostream>
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;

class Dis{
public:
	int endCity;
	int distance;
	Dis():endCity(0), distance(0) {}
	Dis(int city,int dis){
		endCity = city;
		distance = dis;
	}
};
class PathInfo{
public:
	int distance;
	int pathNum;
	int maxRescue;
	PathInfo():distance(0),pathNum(0),maxRescue(0) {}
	PathInfo(int dis, int num,int rescue){
		distance = dis;
		pathNum = num;
		maxRescue = rescue;
	};
};

int main()
{
#ifndef ONLINE_JUDGE
	freopen("D:/in.txt","r",stdin);
	freopen("D:/out.txt","w",stdout);
#endif
	//get basic information
	int N, M, C1, C2;
	cin >> N >> M >> C1 >> C2;
	//get rescue Num
	vector<int> rescue;
	rescue.resize(N);
	for(int i = 0;i < N;++i){
		cin >> rescue[i];
	}
	//get distance between city
	const int infinity = 0x7fffffff;
	int c1,c2,dis;
    map<int,vector<Dis> > Distances;
	for(int i = 0;i < M;++i){
		cin >> c1 >> c2 >> dis;
		Distances[c1].push_back(Dis(c2,dis));
		Distances[c2].push_back(Dis(c1,dis));
	}
	//get shortest path
	vector<PathInfo> paths(N);
	for(int i = 0;i < Distances[C1].size();++i){
		int city = Distances[C1][i].endCity;
		paths[city] = PathInfo(Distances[C1][i].distance,1,rescue[C1] + rescue[city]);
	}

	vector<bool> final(N);
	final[C1] = true;
	while(!final[C2]){
		int minDis = infinity;
		int sel;
		for(int j = 0;j < Distances[C1].size();++j){
			int city = Distances[C1][j].endCity;
			if(final[city]){
				continue;
			}
			int dis = Distances[C1][j].distance;
			if (dis <= minDis){
				minDis = dis;
				sel = city;
			}
		}
		if (sel == C2){
			break;
		}
		final[sel] = true;
		for(int j = 0;j< Distances[sel].size();++j){
			int city = Distances[sel][j].endCity;
			if(final[city]){
				continue;
			}
			int dis = Distances[sel][j].distance;
			int newDis = minDis + dis;
			if(paths[city].distance == 0 || newDis < paths[city].distance){
				paths[city] = PathInfo(newDis,paths[sel].pathNum,paths[sel].maxRescue + rescue[city]);
			}else if(newDis == paths[city].distance){
				paths[city].pathNum += paths[sel].pathNum;
				if(paths[sel].maxRescue + rescue[city] > paths[city].maxRescue){
					paths[city].maxRescue = paths[sel].maxRescue + rescue[city];
				}
			}
		}
	}
	cout << paths[C2].pathNum << " " << paths[C2].maxRescue << endl;

#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
#endif

}
