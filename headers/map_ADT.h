#include <parsing_struct.h>
#include <string>

#ifndef CUSTOM_MAP_ADT_H
#define CUSTOM_MAP_ADT_H

template <typename KeyType, typename DataType>
class MapADT {
    virtual DataType get(KeyType key);
    virtual DataType put(KeyType key, DataType data);
    virtual DataType remove(KeyType key);
    virtual int size();
    virtual bool isEmpty();
};

#endif