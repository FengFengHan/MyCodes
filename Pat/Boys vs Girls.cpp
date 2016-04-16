//
// Created by Han on 16/3/10.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Student{
public:
    string name_;
    string id_;
    int grade_;
    Student():grade_(-1) {}
    Student(string name, string id, int grade){
        name_ = name;
        id_ = id;
        grade_ = grade;
    }
};
bool cmp(const Student& s1, const Student& s2)
{
    return s1.grade_ > s2.grade_;
}

vector<Student> males;
vector<Student> females;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    int N;
    cin >> N;
    string name, gender, id;
    int grade;
    for(int i =0; i < N; ++i){
        cin >> name >> gender >> id >> grade;
        Student student(name,id,grade);
        if(gender == "M"){
            males.push_back(student);
        }else{
            females.push_back(student);
        }
    }
    sort(females.begin(),females.end(),cmp);
    sort(males.begin(),males.end(),cmp);
    if(females.size() == 0){
        cout << "Absent" << endl;
    }else{
        cout << females[0].name_ << " " << females[0].id_ << endl;
    }
    int male_num = males.size();
    if(male_num == 0){
        cout << "Absent" << endl;
    }else{
        cout << males[male_num-1].name_ << " " << males[male_num-1].id_ << endl;
    }
    if(females.size() == 0 || males.size() == 0){
        cout << "NA" << endl;
    }else{
        cout << females[0].grade_ - males[male_num-1].grade_ << endl;
    }
}