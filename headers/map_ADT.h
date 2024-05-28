#include <parsing_struct.h>
#include <string>

#ifndef CUSTOM_MAP_ADT_H
#define CUSTOM_MAP_ADT_H

template <typename dataT>
class Map_ULL {
    virtual dataT get(unsigned long long int key);
    virtual dataT put(unsigned long long int key, dataT data);
    virtual dataT remove(unsigned long long int key);
    virtual int size();
    virtual bool isEmpty();
};

template <typename dataT>
class Map_S {
    virtual dataT get(std::string key);
    virtual dataT put(std::string key, dataT data);
    virtual dataT remove(std::string key);
    virtual int size();
    virtual bool isEmpty();
};

struct Pair_ULL {
    unsigned long long int key;
    twtdata value;
};

struct Pair_S {
    std::string key;
    twtdata value;
};

#endif