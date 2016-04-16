#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main()
{
	/*#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdin);
	#endif*/
	int a,b,c;
	while (cin>>a>>b){
		c = a +b;
		string s;
		stringstream ss;
		ss << (c <0 ? -c : c);
		ss >> s;
		for(int i = s.size() -3 ; i> 0; i -= 3){
			s.insert(i, 1, ',');
		}
                if( c < 0){
			s.insert(0,1,'-');
		}
	cout << s << endl;
	}
	/*#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif*/
}
