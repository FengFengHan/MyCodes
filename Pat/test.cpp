#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Account{
public:
    string name_;
    string password_;
    Account(){}
    Account(string name, string password){
        name_=name;
        password_ = password;
    }
};


