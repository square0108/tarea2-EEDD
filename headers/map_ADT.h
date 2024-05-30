#include <parsing_struct.h>
#include <string>

#ifndef CUSTOM_MAP_ADT_H
#define CUSTOM_MAP_ADT_H

template <typename KeyType, typename ValueType>
class MapADT {
    public:
        virtual ValueType get(KeyType) = 0;
        virtual ValueType put(KeyType, ValueType) = 0;
        virtual ValueType remove(KeyType) = 0;
        virtual int size() = 0;
        virtual bool isEmpty() = 0;
};

#endif