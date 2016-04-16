#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;
class gradeRecord
{
public:
	int A;
	int C;
	int M;
	int E;
	gradeRecord():A(0), C(0), M(0), E(0) {}
	gradeRecord(int a, int c, int m,int e){
		A =a;
		C = c;
		M = m;
		E = e;
	}
};
bool cmp(const int &a, const int &b){
	if( a > b){
		return true;
	}
	return false;
}

void getRank(int* grades,int num, map<int,int>& grade2Rank){
	sort(grades, grades + num, cmp);
	for(int i = 0;i < num;i++){
		if(grade2Rank.count(grades[i])){
			continue;
		}
		grade2Rank[grades[i]] = i + 1;
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("D:/in.txt","r",stdin);
#endif
	int N,M;
	cin >> N >> M;

	int AG[2000],CG[2000], MG[2000],EG[2000];
	string studentId;
	int a,c,m,e;
	map<string,gradeRecord> studentRecord;
	for(int i = 0; i < N;++i){
		cin >> studentId >> c >> m >> e;
		a = (c + m + e)/3;
		studentRecord[studentId] = gradeRecord(a,c,m,e);
		AG[i] = a;
		CG[i] = c;
		MG[i] = m;
		EG[i] = e;
	}

	vector<string> students;
	students.resize(M);
	for(int i = 0; i < M;++i){
		cin >> students[i];
	}

	map<int,int> AG2Rank;
	getRank(AG,N,AG2Rank);
	map<int,int> CG2Rank;
	getRank(CG,N,CG2Rank);
	map<int,int> MG2Rank;
	getRank(MG,N,MG2Rank);
	map<int,int> EG2Rank;
	getRank(EG,N,EG2Rank);

	for(size_t i=0;i < students.size();++i){
		if(studentRecord.count(students[i]) == 0){
			cout << "N/A" << endl;
			continue;
		}
		gradeRecord record = studentRecord[students[i]];
		int ranks[] = {AG2Rank[record.A], CG2Rank[record.C], MG2Rank[record.M], EG2Rank[record.E]};
		char courses[] = {'A', 'C', 'M', 'E'};
		char bestCourses = courses[0];
		int bestRank = ranks[0];
		for(int i = 1; i < 4; ++i){
			if(ranks[i] < bestRank){
				bestRank = ranks[i];
				bestCourses = courses[i];
			}
		}
		cout << bestRank << " " << bestCourses << endl;
	}
#ifndef ONLINE_JUDGE
	fclose(stdin);
#endif
}