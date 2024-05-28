#include <parsing_struct.h>
#include <map_ADT.h>
#include <string>
#include <forward_list>
#include <math.h>

#ifndef OPEN_HASH_TABLE
#define OPEN_HASH_TABLE
#define MAX_ATTEMPTS 100

class OpenHash_ULL : Map_ULL<twtdata> {
    private:
        int arr_size;
        std::forward_list<twtdata> *arr;
        int (*hashing_method)(unsigned long long int, int, int);
    public:
        OpenHash_ULL(int s, int (*hashing_method)(unsigned long long int, int, int)) {
            this->arr_size = s;
            this->arr = new std::forward_list<twtdata>[arr_size];
            this->hashing_method = hashing_method;
        }
        
        twtdata get(unsigned long long int key);
        
        twtdata put(unsigned long long int key, twtdata data) {
            int idx = hashing_method(key, arr_size, MAX_ATTEMPTS);
            std::forward_list<twtdata> indexed_list = arr[idx];
            for (auto& entry : indexed_list) {
                
            }
        }
        
        twtdata remove(unsigned long long int key);
        
        int size() {
            return arr_size;
        }

        bool isEmpty() {
            for (int i = 0; i < arr_size; i++) {
                if (!(arr[i].empty())) {
                    return false;
                }
            }
            return true;
        }
};

#endif