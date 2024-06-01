#include <iostream>
#include <string>
#include <vector>
#include "map_ADT.h"
#include "hash_functions.h"

using namespace std;

#ifndef CLOSED_HASH_H
#define CLOSED_HASH_H

#define INF 99999
#define INTENTOS_MAXIMOS 400
#define MIN_TABLE_SIZE 11

enum probing_type {
    LINEAR_PROBING,QUADRATIC_PROBING,DOUBLE_HASHING
};

// Vacio: Nunca ha almacenado un objeto, Ocupado: lo que dice, Disponible: Tenia un objeto, pero fue eliminado.
enum position_status {
    VACIO,OCUPADO,DISPONIBLE
};

/* Struct de 3 elementos que guarda una llave, valor, y el estado de la tupla (ver enum position_status)
*/
template <typename T1, typename T2>
struct Tupla_Hash 
{
    T1 key;
    T2 value;
    position_status status = VACIO;

    void update(T1 a, T2 b, position_status c) {
        this->key = a;
        this->value = b;
        this->status = c;
    }
};

/* Clase que implementa la tabla con Hash Cerrado 
*/
template <typename KeyType, typename ValueType>
class ClosedHashTable : public MapADT<KeyType,ValueType>
{
    public:

    // Variables privadas

    const ValueType DEFAULT_VALUE;
    probing_type _probing_method;
    std::vector<Tupla_Hash<KeyType,ValueType>> *_container;
    int _container_cap;
    int _used_buckets = 0;
    int (* _hashing_method)(KeyType /*clave*/,int /*tamaño arreglo*/);

    // Funciones privadas

    int  _linear_probing(KeyType key, int size, int attempt);
    int _quadratic_probing(KeyType key, int size, int attempt);
    int _double_hashing(KeyType key, int size, int attempt);

    // Funciones publicas (prototipos)

    ClosedHashTable(int size, int (*hashing_func)(KeyType, int), probing_type probingtype);
    ValueType get(KeyType key);
    ValueType put(KeyType key, ValueType value);
    ValueType remove(KeyType key);
    int size();
    bool isEmpty();
    void debug_print_container();
};

//Implementacion de Funciones

template <typename KeyType, typename ValueType>
ClosedHashTable<KeyType,ValueType>::ClosedHashTable(int size, int (*hashing_func)(KeyType, int), probing_type probingtype) 
{
    this->_container = new std::vector<Tupla_Hash<KeyType,ValueType>>;
    this->_hashing_method = hashing_func;
    this->_probing_method = probingtype;

    // Asignar el tamaño deseado INICIAL de la tabla al vector contenedor
    if (size < MIN_TABLE_SIZE)
        this->_container->reserve(MIN_TABLE_SIZE);
    else 
        this->_container->reserve(size);
    this->_container_cap = _container->capacity();

    // Se inicializan todas las tuplas de la tabla de forma "vacía"
    for (int i = 0; i < (int)_container->capacity(); i++) {
        Tupla_Hash<KeyType,ValueType> init;
        _container->push_back(init);
    }

}

/* Busca un elemento en la tabla. Debe comprobar cual modo de probing usar.
*/
template <typename KeyType, typename ValueType>
ValueType ClosedHashTable<KeyType,ValueType>::get(KeyType clave_ingresada)
{
    // _hashing_method es utilizado dentro de las funciones probing, por lo que no es necesario llamarlo direcetamente aqui.
    for (int i = 0; i < INF; i++) {
        int hashed_idx;
        switch (_probing_method) {
            case LINEAR_PROBING:
                hashed_idx = _linear_probing(clave_ingresada, _container_cap, i);
                break;
            case QUADRATIC_PROBING:
                hashed_idx = _quadratic_probing(clave_ingresada, _container_cap, i);
                break;
            case DOUBLE_HASHING:
                hashed_idx = _double_hashing(clave_ingresada, _container_cap, i);
                break;
            default:
                std::cout << "Error: No probing type detected" << std::endl;
                exit(EXIT_FAILURE);
        }
        Tupla_Hash<KeyType,ValueType> tupla_at_idx = _container->at(hashed_idx);

        // Compara la clave que se busca con la clave de toda posición ocupada que encuentre
        if (tupla_at_idx.status == OCUPADO && tupla_at_idx.key == clave_ingresada) 
            return tupla_at_idx.value;

        // Si encuentra una posición vacía, entonces la clave no había sido ingresada a la tabla.
        else if (tupla_at_idx.status == VACIO)
            return DEFAULT_VALUE;
    }
    std::cout << "Numero maximo de intentos alcanzados en la búsqueda de la clave" << std::endl;
    return DEFAULT_VALUE;
}

/* Inserta un nuevo elemento en la tabla. Debe comprobar cual modo de probing usar.
* 
* NOTAS IMPORTANTES:
* - Intentar insertar un elemento que ya se encuentra en la tabla no sobreescribe el valor. (devuelve el valor ingresado)
* - Insertar un elemento exitosamente devuelve DEFAULT_VALUE
*/
template <typename KeyType, typename ValueType>
ValueType ClosedHashTable<KeyType,ValueType>::put(KeyType clave_ingresada, ValueType valor_ingresado)
{
    for (int i = 0; i < INF; i++) {
        int hashed_idx;
        switch (_probing_method) {
            case LINEAR_PROBING:
                hashed_idx = _linear_probing(clave_ingresada, _container_cap, i);
                break;
            case QUADRATIC_PROBING:
                hashed_idx = _quadratic_probing(clave_ingresada, _container_cap, i);
                break;
            case DOUBLE_HASHING:
                hashed_idx = _double_hashing(clave_ingresada, _container_cap, i);
                break;
            default:
                std::cout << "Error: No probing type detected" << std::endl;
                exit(EXIT_FAILURE);
        }
        Tupla_Hash<KeyType,ValueType> tupla_at_idx = _container->at(hashed_idx);

        if (tupla_at_idx.status == VACIO || tupla_at_idx.status == DISPONIBLE) {
            (_container->at(hashed_idx)).update(clave_ingresada,valor_ingresado,OCUPADO);
            return DEFAULT_VALUE;
        }
    }
    // Si llega aqui, la inserción falló.
    std::cout << "Intentos maximos alcanzados." << std::endl;
    return valor_ingresado;
}

template <typename KeyType, typename ValueType>
ValueType ClosedHashTable<KeyType,ValueType>::remove(KeyType _alguien)
{
    
}

template <typename KeyType,typename ValueType>
int ClosedHashTable<KeyType,ValueType>::size()
{
    return _container_cap;
}

template <typename KeyType,typename ValueType>
bool ClosedHashTable<KeyType,ValueType>::isEmpty()
{
    return _container->empty();
}

template <typename KeyType,typename ValueType>
int ClosedHashTable<KeyType,ValueType>::_linear_probing(KeyType key, int size, int attempt) {
    return (_hashing_method(key,size) + attempt) % size;
}

template <typename KeyType,typename ValueType>
int ClosedHashTable<KeyType,ValueType>::_quadratic_probing(KeyType key, int size, int attempt) {
    return (_hashing_method(key,size) + attempt*attempt) % size;
}

template <typename KeyType,typename ValueType>
int ClosedHashTable<KeyType,ValueType>::_double_hashing(KeyType key, int size, int attempt) {
    int hashed_key = _hashing_method(key,size);
    return (hashed_key + attempt*(doublehash_h2(hashed_key))) % size;
}

#endif