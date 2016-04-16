//
// Created by Han on 16/3/10.
//
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

map <char, char> repl;///////???????????
//repl['1'] = '@';wrong
//repl['0'] = '%';
//repl['l'] = 'L';
//repl['O'] = 'o';

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    repl['1'] = '@';
    repl['0'] = '%';
    repl['l'] = 'L';
    repl['O'] = 'o';
    vector<Account> modi_accounts;
    int N;
    cin >> N;
    string name,password;
    bool modified = false;
    for(int i=0; i < N; ++i) {
        modified = false;
        cin >> name >> password;
        for(int j=0; j<password.size();++j){

               if(repl.find(password[j]) != repl.end()) {
                   modified = true;
                   password[j] = repl[password[j]];
               }
        }
        if(modified){
            Account account(name,password);
            modi_accounts.push_back(account);
        }
    }
    if(modi_accounts.size() > 0){
        cout << modi_accounts.size() << endl;
        for(int i=0;i<modi_accounts.size();++i){
            cout << modi_accounts[i].name_ << " " << modi_accounts[i].password_ << endl;
        }
    }else{
        if(N == 1){
            cout << "There is " << 1 << " account and no account is modified" << endl;
        }else{
            cout << "There are " << N << " accounts and no account is modified" << endl;
        }
    }

}
