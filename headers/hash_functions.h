#include <math.h>
#include <string>
#include <vector>

#ifndef CUSTOM_HASH_FUNCTIONS_H
#define CUSTOM_HASH_FUNCTIONS_H

const unsigned int _POLY_Z = 33; // Constante Z para polinomio de acumulacion (string hashing)

/* Funciones de compresión con clave UNSIGNED LONG LONG INT */

// Metodo de la division
int h_div(unsigned long long int key, int size) 
{
    return key % size;
}

// Metodo multiply, add and divide
int h_MAD(unsigned long long int key, int mult, int add, int size) 
{
    if (mult % size == 0) {
        // idk
        return h_MAD(key, 1, add, size);
    }
    return (int)((mult*key + add) % size);
}

/* Hash Codes con clave ULL */

// Component Sum (dos particiones de 32 bits. Implementacion cortesía del PPT 8: Diccionarios)
int hc_compsum(unsigned long long int i) 
{
    return ((int) i + (int) (i>>32));
}

// Funciones "completas"
int CSandCompress(unsigned long long int key, int size) 
{
    return h_div((unsigned long long int)hc_compsum(key),size);
}

// solo para debugging, NO USAR para experimentos
/*
int bogohash(unsigned long long int key, int size) 
{
    return 0;
}
*/

/* Hash Codes con clave String*/

// Acumulacion polinomial
unsigned long long int poly_accumulation(std::string key) 
{
    unsigned int poly_eval = 0;
    int z_exp = 0;
    for (auto& c : key) {
        poly_eval += ((int)c)*pow(_POLY_Z,z_exp);
        z_exp++;
    }
    return poly_eval;
}

// Funciones "completas"

int string_hash(std::string key, int size) {
    return h_div(poly_accumulation(key),size);
}


#endif