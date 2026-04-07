#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "functions.hpp"
#include "json/json.h"

int main(int argc, char* argv[]) {
    std::string prob_no = argv[1];
    std::string filename = argv[2];

    Json::Value root;
    ParseJSON(filename, root);

    if (prob_no == "a") {
        if (argc != 3) {
            std::cout << "Please check your command line arguments, "
                         "Problem (a) requires two command line arguments: "
                         "[Problem no.] [JSON file name]"
                      << std::endl;
            return -1;
        }

        std::cout << "Parsed JSON content:" << std::endl;
        std::cout << root << std::endl;

    } else if (prob_no == "b") {
        if (argc != 4) {
            std::cout << "Please check your command line arguments, "
                         "Problem (b) requires three command line arguments: "
                         "[Problem no.] [JSON file name] [Target key]"
                      << std::endl;
            return -1;
        }

        std::string target_key = argv[3];
        std::unique_ptr<std::string> res = CheckTarget(root, target_key);
        if (res) {
            std::cout << *res;
        } else {
            std::cout << target_key << " does not exist in JSON file.";
        }

    } else if (prob_no == "c") {
        if (argc != 3) {
            std::cout << "Please check your command line arguments, "
                         "Problem (c) requires two command line arguments: "
                         "[Problem no.] [JSON file name]"
                      << std::endl;
            return -1;
        }

        std::list<std::string> lst;
        CompleteList(root, lst);
        for (const auto& item : lst) {
            std::cout << item << std::endl;
        }

    } else if (prob_no == "d") {
        if (argc != 6) {
            std::cout << "Please check your command line arguments, "
                         "Problem (d) requires five command line arguments: "
                         "[Problem no.] [JSON file name] [Key name 1] "
                         "[Key name 2] [Output file name]"
                      << std::endl;
            return -1;
        }

        std::string key1 = argv[3];
        std::string key2 = argv[4];
        std::string out_filename = argv[5];
        SumTwoMembers(key1, key2, out_filename, root);

    } else {
        std::cout
            << "Invalid problem number. Please provide 'a', 'b', 'c', or 'd'."
            << std::endl;
        return -1;
    }

    return 0;
}
