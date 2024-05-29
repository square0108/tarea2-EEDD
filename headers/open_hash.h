#include <parsing_struct.h>
#include <map_ADT.h>
#include <string>
#include <forward_list>
#include <list>
#include <math.h>
#include <iostream>
#include <vector>
#include <iterator>

#ifndef OPEN_HASH_TABLE
#define OPEN_HASH_TABLE
#define MAX_ATTEMPTS 100

template<typename KeyType, typename ValueType>
class OpenHashTable : MapADT<KeyType, ValueType> {
    private:
        // TODO
        void _rehash() {

        }
    public:
        int arr_size; // Tamaño del arreglo contenedor
        std::forward_list<std::pair<KeyType, ValueType>> *arr; // Cada elemento de este arreglo es una lista enlazada, y cada elemento de la lista enlazada es un par (clave, valor).
        int (*hashing_method)(KeyType /*key*/, int /*size*/); // Puntero a la funcion hash que utilizará la instancia de esta clase.
        const ValueType DEFAULT_VALUE; // Requiere que ValueType tenga constructor por defecto.

        OpenHashTable(int s, int (*hashing_func)(KeyType, int)) {
            this->arr_size = s;
            arr = new std::forward_list<std::pair<KeyType, ValueType>>[arr_size];
            this->hashing_method = hashing_func;
        }

        ~OpenHashTable() {
            delete[] arr;
        }
        
        /* Busca un elemento de la tabla cuya clave coincida con aquella que fue ingresada a la función.
        *
        * PARAMETROS:
        *   - key: Clave que será ingresada a la función hash, en nuestro proyecto es de tipo 64-bit-integer o String.
        * 
        * RETORNO:
        *   - Si no existía ningún elemento con esta clave ingresada en la tabla, o falla la búsqueda, retorna "null".
        *     Si encuentra un elemento con esta clave, retorna el valor asociado a ese elemento.
        */
        ValueType get(KeyType key) {
            int idx = hashing_method(key, arr_size);
            auto *list_at_idx = &arr[idx];
            // std::cout << "[GET] " << "Input key: " << key << ", hashed to: " << idx << std::endl; // debug
            for (std::pair<KeyType,ValueType>& entry : *list_at_idx) {;
                if (key == entry.first) return entry.second;
            }
            std::cout << "Couldn't find any entry with key " << key << std::endl; // debug
            return DEFAULT_VALUE;
        };

        /* Inserción de un par ordenado (clave, valor) a la tabla hash.
        *
        * PARAMETROS:
        *   - key: Clave que será ingresada a la función hash, en nuestro proyecto es de tipo 64-bit-integer o String.
        *   - data: Valor asociado a la clave ingresada. En nuestro proyecto, es un struct que contiene los datos en *una* fila del .csv.
        * 
        * RETORNO:
        *   - Si no existía ningún elemento con esta clave ingresada en la tabla, retorna "null".
        *     Si ya existía un elemento con esta clave en la tabla, retorna el valor que fue reemplazado.
        */
        ValueType put(KeyType key, ValueType data) {
            if (typeid(KeyType) == typeid(unsigned long long int)) {
                // ID Hashing
                int idx = hashing_method(key, arr_size);
                std::pair<KeyType,ValueType> new_entry(key,data);
                auto *list_at_idx = &arr[idx];

                if (list_at_idx->empty()) {
                    list_at_idx->push_front(new_entry);
                    return DEFAULT_VALUE;
                }
                else {
                    for (std::pair<KeyType, ValueType>& entry : *list_at_idx) {
                        if (entry.first == new_entry.first) {
                            ValueType old_value = entry.second;
                            entry.second = new_entry.second;
                            
                            return old_value;
                        }
                    }
                    list_at_idx->push_front(new_entry);
                    return DEFAULT_VALUE;
                }
                std::cout << "Error durante inserción" << std::endl;
                exit(EXIT_FAILURE);
            }
            else if (typeid(KeyType) == typeid(std::string)) {
                // String hashing
                std::cout << "Detected key type: String" << std::endl;
                return DEFAULT_VALUE;
            }
            else {
                std::cout << "No existe funcion hash para este tipo de clave.";
                exit(EXIT_FAILURE);
            }
        }
        
        // TODO
        ValueType remove(KeyType key) {
            int idx = hashing_method(key, arr_size);
            auto *list_at_idx = &arr[idx];
            // Loop chano cortesía de StackOverflow (questions/14373934)
            for (auto iter = list_at_idx->begin(), prev = list_at_idx->before_begin(); iter != list_at_idx->end(); iter++, prev++) {
                if (iter->first == key) {
                    ValueType erased_value = iter->second;
                    list_at_idx->erase_after(prev);
                    return erased_value;
                }
            }
            std::cout << "Nothing to remove" << std::endl;
            return DEFAULT_VALUE;
        };
        
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
        
        // todo
        // std::vector keys();
};


#endif