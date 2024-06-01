#include <math.h>
#include <string>
#include <vector>

#ifndef CUSTOM_HASH_FUNCTIONS_H
#define CUSTOM_HASH_FUNCTIONS_H

const unsigned int _POLY_Z = 33; // Constante Z para polinomio de acumulacion (string hashing)

// Declaracion de funciones

/* Funciones de compresión con clave numérica */
int h_div(unsigned long long int key, int size);
int h_MAD(unsigned long long int key, int mult, int add, int size);
/* Hash Codes con clave numérica */
int hc_compsum(unsigned long long int i);
/* Hash Codes con clave string */
unsigned long long int hc_poly_accumulation(std::string key);
/* Funciones hash listas para usar en tablas */
int CSandCompress(unsigned long long int key, int size);
int string_hash(std::string key, int size);

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

// Component Sum (dos particiones de 32 bits. Implementacion cortesía del PPT 8: Diccionarios)
int hc_compsum(unsigned long long int i) 
{
    return ((int) i + (int) (i>>32));
}

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

// Acumulacion polinomial
unsigned long long int hc_poly_accumulation(std::string key) 
{
    // Este valor es muy importante, reducirlo aumenta la velocidad de insercion, pero podria aumentar el % de colisiones?
    const int MAX_CHARS_TO_ADD = 7;

    unsigned int poly_eval = 0;
    int z_exp = 0;
    int strsize = key.size();

    for (int i = 0; i < strsize && i < MAX_CHARS_TO_ADD; i++) {
        poly_eval += ((int)key.at(i))*pow(_POLY_Z,z_exp);
        z_exp++;
    }
    return poly_eval;
}

int string_hash(std::string key, int size) {
    return h_div(hc_poly_accumulation(key),size);
}

int doublehash_h2(int hashed_key)
{
    return (7 - (hashed_key % 7));
}

#endif