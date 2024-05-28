#include <string>
#include <ctype.h>

#ifndef PARSING_STRUCT_H
#define PARSING_STRUCT_H

enum Column {
    UNIVERSITY,UID,USERNAME,TWEETS,FRIENDS,FOLLOWERS,CREATEDATE
};

class twtdata {
    public:
        std::string university;
        unsigned long long int user_id;
        std::string username;
        int number_tweets;
        int friends_count;
        int followers_count;
        std::string created_at;
        
        twtdata () {
            this->university = "";
            this->user_id = 0;
            this->username = "";
            this->number_tweets = 0;
            this->friends_count = 0;
            this->followers_count = 0;
            this->created_at = "";
        }
        void init_from_str(int col, std::string input) {
            switch (col) {
                case UNIVERSITY:
                    this->university = input;
                    break;
                case UID:
                    this->user_id = std::stoull(input, 0);
                    break;
                case USERNAME:
                    this->username = input;
                    break;
                case TWEETS:
                    this->number_tweets = std::stoi(input, 0);
                    break;
                case FRIENDS:
                    this->friends_count = std::stoi(input,0);
                    break;
                case FOLLOWERS:
                    this->followers_count = std::stoi(input,0);
                    break;
                case CREATEDATE:
                    this->created_at = input;
                    break;
                default:
                    std::cout << "Error while parsing to class. Col index given: " << col << std::endl;
                    exit(EXIT_FAILURE);
            }
        }
        void print_data() {
            std::cout << university << "; " << user_id << "; " << username << "; " << number_tweets << "; " << friends_count << "; " << followers_count << "; " << created_at << std::endl;
        }
};
#endif