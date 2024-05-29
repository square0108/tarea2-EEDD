#include <parsing_struct.h>
#include <string>

#ifndef CUSTOM_MAP_ADT_H
#define CUSTOM_MAP_ADT_H

template <typename KeyType, typename ValueType>
class MapADT {
    virtual ValueType get(KeyType key) = 0;
    virtual ValueType put(KeyType key, ValueType data) = 0;
    virtual ValueType remove(KeyType key) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
};

#endif