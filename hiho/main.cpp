#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

typedef long long LL;
//typedef __int64 LL;

string int2string(int a)
{
    stringstream ss;
    ss << a;
    string res;
    res = ss.str();
    return res;
}

int string2int(string s)
{
    stringstream ss;
    ss << s;
    int res;
    ss >> res;
    return res;
}

multimap<int,int> a;

class Test{
public:
    int a_;
    int b_;
    Test(int a,int b){
        a_ = a;
        b_ = b;
    }
};

bool operator==(const Test& test1, const Test& test2)
{
    return (test1.a_ == test2.a_);
}
size_t hash_value(const Test& test){
    size_t seed = 0;
    std::hash_combine(seed, std::hash_value(test.a_));
    std::hash_combine(seed, std::hash_value(test.b_));
    return seed;
}

int main() {
#ifndef ONLINE_JUDGE
    //freopen("/Users/HAN/Documents/in.txt","r",stdin);
#endif
    std::map<int,int> m1;
    set<int> s1;
    m1[34] = 56;
    m1.erase(34);
    s1.insert(34);
    s1.erase(34);

    multimap<int,int> m2;
    //m2.insert(pair<int,int>(34, 56));
    multimap<int,char*> m;
    //multimap的插入只能用insert()不能用数组
    //m.insert(pair<int,char*>(1,"apple"));
    //m.insert(pair<int,char*>(1,"pear"));

   a.insert(make_pair(10,11));

    multiset<int> s2;
    s2.insert(10);
   // cout << a.erase(10) << endl;

    Test test = Test(1,2);
    typedef  unordered_map<Test,int> umap;
    umap temp;
    temp.insert(umap::value_type(test,6));
    return 0;
}