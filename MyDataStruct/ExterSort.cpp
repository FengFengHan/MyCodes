//
// Created by Han on 16/5/2.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

const int  MYMAX = 123456789;
const int  MYMIN = -123456789;

int invalid_count = 0;

void Adjust_LoserTree(int s,vector<int>& loser_tree,const vector<int>& input_vals)
{
    int K = loser_tree.size();
    int parent = (s+K)/2;//notice
    while(parent > 0){
        if(input_vals[s] > input_vals[loser_tree[parent]]){ // s为当前胜者
            int tmp = s;
            s = loser_tree[parent];
            loser_tree[parent] = tmp;
        }
        parent = parent/2;
    }
    loser_tree[0] = s;
}

void Build_LoserTree(vector<int>& loser_tree, vector<int>& input_vals)
{
    int K = input_vals.size() -1;
    loser_tree.resize(K);
    //init
    input_vals[K] = MYMIN;
    for(size_t i=1;i<K;++i){
        loser_tree[i] = K;
    }

    for(int i=K-1;i>=0;--i){
        Adjust_LoserTree(i,loser_tree,input_vals);
    }
}

int get_value(ifstream& i_fstream, bool& if_valid)
{
    int res_val = MYMAX;
    int val;
    if(if_valid){
        if(i_fstream >> val){ //未达到eof
            res_val = val;
        } else{
            if_valid = false;
            invalid_count += 1;
        }
    }
    return res_val;
}

void Merge_KSort(vector<ifstream*> &i_fstreams,ofstream* o_fstream)
{

    size_t K = i_fstreams.size();
    bool* valid_streams = new bool[K]();
    for(size_t i=0;i<K;++i){
        valid_streams[i] = true;
    }
    vector<int> input_vals;
    input_vals.resize(K+1);//facilitate to build loser tree
    for(size_t i=0;i<K;++i){
        input_vals[i] = get_value(*(i_fstreams[i]),valid_streams[i]);
    }
    //Build loser tree
    vector<int> loser_tree;
    Build_LoserTree(loser_tree,input_vals);
    //find min and adjust
    while(invalid_count < K){
        int sel_id = loser_tree[0];
        *o_fstream << input_vals[sel_id] << " " << flush;
        input_vals[sel_id] = get_value(*(i_fstreams[sel_id]),valid_streams[sel_id]);
        Adjust_LoserTree(sel_id,loser_tree,input_vals);
    }
    //close stream
    for(size_t i=0;i<i_fstreams.size();++i){
        (*(i_fstreams[i])).close();
    }
    (*o_fstream).close();
}

void InterSort(string file_name)
{
    ifstream i_fstream(file_name);
    vector<int> vals;
    int val;
    while(i_fstream >> val){
        vals.push_back(val);
    }
    sort(vals.begin(),vals.end());
    i_fstream.close();

    ofstream o_fstream(file_name);
    for(size_t i=0;i < vals.size();++i){
        o_fstream << vals[i] << " " << flush;
    }
    o_fstream.close();
}

int main()
{
    //input files
    vector<string> file_names;
    string my_dir = "/Users/HAN/Documents/";
    file_names.push_back(my_dir + "data1.txt");
    file_names.push_back(my_dir + "data2.txt");
    file_names.push_back(my_dir + "data3.txt");
    size_t K = file_names.size();
    //InterSort for every file
    for(size_t i=0;i<K;++i){
        InterSort(file_names[i]);
    }
    //input streams
    vector<ifstream*> input_streams;
    for(size_t i=0;i<K;++i){
        ifstream* input_stream = new ifstream(file_names[i]);
        input_streams.push_back(input_stream);
    }
    //output file
    string output_file = my_dir +  "data.txt";
    ofstream output_stream(output_file);
    //merger sort for k input streams to output stream
    Merge_KSort(input_streams,&output_stream);
}