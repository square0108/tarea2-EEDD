#include <string>

#ifndef PARSING_STRUCT_H
#define PARSING_STRUCT_H
class uniflw_values {
    public:
        std::string university;
        unsigned long long int user_id;
        std::string username;
        int number_tweets;
        int friends_count;
        int followers_count;
        std::string created_at;
        uniflw_values(std::string university, unsigned long long int user_id, std::string username, int number_tweets, int friends_count, int followers_count, std::string created_at) : 
        university(university), user_id(user_id), username(username), number_tweets(number_tweets), friends_count(friends_count), followers_count(followers_count), created_at(created_at)
        {}
};
#endif