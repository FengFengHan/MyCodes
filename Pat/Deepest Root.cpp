#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
int Tree[10001];

int dfs(int root,const vector<vector<int>>& edges,vector<bool>& visit);

int findRoot(int x){
	if(Tree[x] == -1){
		return x;
	}else{
		int ret = findRoot(Tree[x]);
		Tree[x] = ret;
		return ret;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("D:/in.txt","r",stdin);
#endif
	int N;
	cin >> N;
	for(int i = 0; i<= N;++i){
		Tree[i] = -1;
	}
	vector<vector<int>> edges;
	edges.resize(N+1);
	int a,b;
	int root1,root2;
	for(int i = 0;i<N-1;++i){
		cin >> a >> b;
		root1 = findRoot(a);
		root2 = findRoot(b);
		if(root2 != root1){
			Tree[root2] = root1;
		}
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	set<int> roots;
	int root;
	for(int i = 1; i <= N; ++i){
		root = findRoot(i);
		if(roots.count(root) == 0){
			roots.insert(root);
		}
	}
	if(roots.size() > 1){
		cout << "Error: " << roots.size() <<" components" << endl;
		return 0;
	}

	int maxdepth = 1;
	vector<int> result;
	result.push_back(1);
	for(int i = 1; i <= N;++i){
		if(edges[i].size() == 1){
			vector<bool> visit;
			visit.resize(N+1);
			int depth = dfs(i,edges,visit);
			if(depth > maxdepth){
				maxdepth = depth;
				result.clear();
				result.push_back(i);
			}else if(depth == maxdepth){
				result.push_back(i);
			}
		}
	}
	sort(result.begin(),result.end());
	for(int i = 0; i < result.size();++i){
		cout << result[i] << endl;
	}
}

int dfs(int root,const vector<vector<int>>& edges,vector<bool>& visit)
{
	visit[root] = true;
	int maxdepth = 1;
	for(size_t i = 0; i < edges[root].size();++i){
		if(visit[edges[root][i]]){
			continue;
		}
		int depth = dfs(edges[root][i],edges,visit) + 1;
		if(depth > maxdepth){
			maxdepth = depth;
		}
	}
	return maxdepth;
}