#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
#include <utility>
#include <chrono>
#include "open_hash.h"
#include "hash_functions.h"
#include "parsing_struct.h"
#include "csv_data_insertion.h"

int main(int argc, char **argv)
{
    if (argc != 4)
        std::cout << "Invalid syntax. Usage: ./main <table type> <key type> <number of insertions>" << std::endl;
    
    std::ifstream twitter_csv;
    twitter_csv.open("universities_followers.csv", std::ifstream::in);
    
    if (strcmp(argv[2],"username") == 0) {
        if (strcmp(argv[1],"STL_map") == 0) {
            std::unordered_map<std::string,twtdata> map;
        }
        else if (strcmp(argv[1],"open_hash") == 0) {
            udec::OpenHashTable<std::string,twtdata> table(22189,string_hash);
            udec::insert_lines(twitter_csv,table,(size_t)atoi(argv[3]));
        }
        else if (strcmp(argv[1],"closed_hash") == 0) {
            return 0;
        }
    }
    else if (strcmp(argv[2],"user_id") == 0) {
        if (strcmp(argv[1],"STL_map") == 0) {
            std::unordered_map<unsigned long long int,twtdata> map;
        }
        else if (strcmp(argv[1],"open_hash") == 0) {
            udec::OpenHashTable<unsigned long long int,twtdata> table(22189,CSandCompress);
            udec::insert_lines(twitter_csv,table,(size_t)atoi(argv[3]));
        }
        else if (strcmp(argv[1],"closed_hash") == 0) {
            return 0;
        }
    }
    else {
        std::cout << "Invalid hash key parameter. Possible key types: username, user_id" << std::endl;
        return -1;
    }

    twitter_csv.close();
    return 0;
}
