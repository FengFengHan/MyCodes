//
// Created by Han on 16/3/9.
//
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <sstream>

using namespace std;

class Time{
public:
    int month_;
    int day_;
    int hour_;
    int minute_;
    Time():month_(0), day_(0),hour_(0),minute_(0){} //it is must
    Time(string dateFormat){
      sscanf(dateFormat.c_str(),"%d:%d:%d:%d",&month_,&day_,&hour_,&minute_);
    }
    Time(int month, int day, int hour, int minute){
        month_ = month;
        day_ = day;
        hour_ = hour;
        minute_ = minute;
    }
    bool operator<(const Time& time) const{
        if(this->day_ != time.day_){

            return this->day_ < time.day_;

        }else if(this->hour_ != time.hour_){

            return this->hour_ < time.hour_;

        }else if(this->minute_ != time.minute_){

            return this->minute_ < time.minute_;

        }else{
            return true;
        }
    }
};
class Record{
public:
    string name_;
    Time time_;
    string status_;
    Record():name_(""), status_("") {}
    Record(string name,Time time, string status){
        name_ = name;
        time_ = time;
        status_ = status;
    }
    bool operator<(const Record &r) const{
        bool res;
        if(this->name_ != r.name_){

            res = this->name_ < r.name_;

        }else {
            res = this->time_ < r.time_;
        }
        return res;
    }
};



class Call{
public:
    Time start_;
    Time end_;
    int dur_time_;
    int cost_;
    Call():start_("") {}
    Call(Time start, Time end,const int* rates){
        start_ = start;
        end_ = end;
        dur_time_ = GetMibutes(end) - GetMibutes(start);
        cost_ = GetCost(start,end,rates);
    }
    int GetMibutes(Time time){
        return (time.day_*24*60 + 60*time.hour_ + time.minute_);
    }
    int GetCost(Time start, Time end, const int* rates){
        Time base(0,start.day_,0,0);
        //cost_start:cost between start and base
        int cost_start = 0;
        for(int i=0;i<start.hour_;++i){
            cost_start += (rates[i] * 60);
        }
        cost_start += rates[start.hour_] * start.minute_;
        //cost_end:cost between end and base
        int cost_end = 0;
        int day_cost = 0;
        for(int i =0;i<24;++i){
            day_cost += rates[i]*60;
        }
        cost_end += day_cost * (end.day_ - start.day_);
        for(int i=0;i<end.hour_;++i){
            cost_end += (rates[i] * 60);
        }
        cost_end += rates[end.hour_] * end.minute_;
        //real cost
        int cost = cost_end - cost_start;
        return cost;
    }
};

string time2string(Time time){
    char res[9];
    sprintf(res,"%02d:%02d:%02d",time.day_,time.hour_,time.minute_);
    return string(res);
}

int rates[24];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("/Users/HAN/Documents/Pat/in.txt","r",stdin);
    freopen("/Users/HAN/Documents/Pat/out.txt","w",stdout);
#endif
    for(int i=0; i< 24;++i){
        cin >> rates[i];
    }
    //save records
    int N;
    cin >> N;
    vector<Record> Records;
    string name,timeFormat,status;
    for(int i=0; i < N; ++i){
        cin >> name >> timeFormat >> status;
        Time time = Time(timeFormat);
        Record record(name,time,status);
        Records.push_back(record);
    }
    //records to call
    sort(Records.begin(),Records.end()); /////////there is problem
    map<string, vector<Call> > customers;
    for(int i= 0;i< N-1;++i){
        Record record1 = Records[i];
        Record record2 = Records[i+1];
        if(record1.status_ == "on-line" and record2.status_ == "off-line"){
            Call call(record1.time_,record2.time_,rates);
            customers[record1.name_].push_back(call);
        }
    }
    //output
    map<string,vector<Call> >::const_iterator it = customers.begin();
    while(it != customers.end() ){
        name = it->first;
        int month = (Records[0].time_).month_;
        int total = 0;
        printf("%s %02d\n",name.c_str(),month);
        vector<Call> customer_calls = it->second;
        for(int i = 0;i<customer_calls.size();++i){
            Call call = customer_calls[i];
            printf("%s %s %d $%.2lf\n", (time2string(call.start_)).c_str(),
                   (time2string(call.end_)).c_str(),
            call.dur_time_,call.cost_/100.0);
            total += call.cost_;
        }
        printf("Total amount: $%.2lf\n", ((double)total/100) );
        it++;
    }

}