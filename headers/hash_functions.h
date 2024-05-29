#include <math.h>
#include <string>

#ifndef CUSTOM_HASH_FUNCTIONS_H
#define CUSTOM_HASH_FUNCTIONS_H

/* Funciones de compresión con clave UNSIGNED LONG LONG INT */

// Metodo de la division
int h_div(unsigned long long int key, int size) {
    return key % size;
}

// Metodo multiply, add and divide
int h_MAD(unsigned long long int key, int mult, int add, int size) {
    return (int)((mult*key + add) % size);
}

/* Hash Codes con clave ULL */
// Component Sum (dos particiones de 32 bits. Implementacion cortesía del PPT 8: Diccionarios)
int hc_compsum(unsigned long long int i) {
    return ((int) i + (int) (i>>32));
}

// Funciones "completas"
int CSandCompress(unsigned long long int key, int size) {
    return h_div((unsigned long long int)hc_compsum(key),size);
}

/* Funciones con clave STRING */

#endif