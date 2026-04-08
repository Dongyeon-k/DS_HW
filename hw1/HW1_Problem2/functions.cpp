#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "json/json.h"

using namespace std;

void ParseJSON(const std::string filename, Json::Value& json_object) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "The file isn't opened" << endl;
        return;
    }

    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;

    string error;
    
    if (!Json::parseFromStream(builder, file, &json_object, &error)) {
        cerr << "Failed to parse JSON: " << error << endl;
        json_object = Json::Value();
        return;
    }
    file.close();
    return;
}

std::unique_ptr<std::string> CheckTarget(const Json::Value& json_object, std::string& target_key) {
    if (json_object.isMember(target_key)){
        return make_unique<string>(json_object[target_key].asString());
    }
    else{
        return nullptr;
    }
}

void CompleteList(const Json::Value& json_object, std::list<std::string>& empty_list) {
    vector<string> keys = json_object.getMemberNames();
    for (string key : keys){
        if (json_object[key].isString()){
            empty_list.push_front(json_object[key].asString());
        }
    }

    // When there is no memeber whose value is a string type
    if(empty_list.size() == 0) {
        empty_list.push_back("NO_STRING");
    }
}

void SumTwoMembers(std::string& key1, std::string& key2, const std::string& out_filename, Json::Value& json_object) {
    auto vec1 = json_object[key1];
    auto vec2 = json_object[key2];

    if((vec1.size() == vec2.size()) && !(vec1.empty())){
        string new_key_name = "SumOf" + key1 + "And" + key2;

        for (int i =0  ; i < vec1.size() ; i++){
            json_object[new_key_name].append(vec1[i].asInt() + vec2[i].asInt());
        }
    }
    
    ofstream file(out_filename);
    if (!file.is_open()){
        cerr << "Writing file isn't open"<<endl;
        return ;
    }
    Json::StyledWriter writer;
    file << writer.write(json_object);
    file.close();
    return;

}
