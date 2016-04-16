//
// Created by Han on 16/3/29.
//

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
T add(T a, T b)
{
    T c;
    return (a+b);
}

template <typename s,typename  t> class My{
public:
    vector<s> push(s a)
    {
        con.push_back(a);
    }
   vector<s> con;
};