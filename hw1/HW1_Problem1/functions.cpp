#include "functions.hpp"

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> line_parser(string line){
    vector<string> result;
    string cur;
    bool in_quotes = false;

    for (char ch : line) {
        if (ch == '"') {
            in_quotes = !in_quotes;
            cur += ch;   // 따옴표도 그대로 저장
        }
        else if (ch == ',' && !in_quotes) {
            result.push_back(cur);
            cur.clear();
        }
        else {
            cur += ch;
        }
    }

    result.push_back(cur);
    return result;

}

bool check_element_number(string line, int n){ 
    vector<string> vec = line_parser(line);

    if(vec.size()==n) {
        return true;
    }
    else{
        return false;
    }
}


void ParseCSV(const string& filename, map<int, string>& header_cols, map<string, vector<string>>& data_map) {
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Failed to open file" << endl;
        return;
    }

    string line;
    // First Line : Header
    if (getline(file, line)){
        int i = 0;
        for (string ele: line_parser(line)) {
            header_cols[i++] = ele;
        }
    }

    // 2 ~ : Data
    while (getline(file, line)){
        // Skip row if different number of elements than the header
        if (check_element_number(line, 3))
        {
            int i = 0;
            for (string ele: line_parser(line)) {
                data_map[header_cols[i++]].push_back(ele);
            }
        }
    }

    file.close();
    return;
}

int SumColumn(const string& column_name, map<string, vector<string>>& data_map) {
    int result = 0;
    for (string num : data_map[column_name]){
        result += stoi(num);
    }
    return result;
}

double FilterMostFrequentAvg(const string& key_col, string& value_col, map<string, vector<string>>& data_map) {
    map<string, int> key_cnt_map;
    map<string, vector<int>> key_index_map;

    int i = 0;
    for (string key : data_map[key_col]){
        key_cnt_map[key]++;
        key_index_map[key].push_back(i++);
    }

    string max_key;
    int max_value = 0;

    for (auto [key, value]: key_cnt_map){
        if(value > max_value){
            max_key = key;
            max_value = value;
        }
    }

    int result = 0;
    for (int idx : key_index_map[max_key]){
        result += stoi(data_map[value_col][idx]);
    }

    return result / max_value;
}

void SumTwoColumns(string& value_col1, string& value_col2, const string& out_filename, map<int, string>& header_cols, map<string, vector<string>>& data_map) {
    ofstream file("output.txt");
    if (!file.is_open()){
        cerr << "Failed to open file" << endl;
        return ;
    }


    file << "ASDFasdfasdf" << endl;



    file.close();
    return ;
} 