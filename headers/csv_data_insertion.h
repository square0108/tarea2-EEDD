#include "datos_usuario.h"
#include "map_ADT.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <type_traits>

#ifndef CSV_PARSING_H
#define CSV_PARSING_H

#define CSV_NUM_COLUMNS 7
#define CSV_NUM_ENTRIES 21070

// activar mensajes de debug
const bool _PARSE_DEBUG = 0;

namespace tarea {

// declaraciones de funciones
std::string SciNot_to_ull(std::string& scinot);
userdata read_row_values(std::string row);
std::vector<userdata> csv_to_vector(std::ifstream& file, size_t n_rows);

// Modifica una string de notación científica a forma decimal (no cambia tipo de dato)
// nota: esta funcion destruye la string de entrada
std::string SciNot_to_ull(std::string& scinot) 
{
    int plus_idx = scinot.find('+');
    int scipow = std::stoi(scinot.substr(plus_idx,scinot.size()-plus_idx));
    scinot.erase(plus_idx-1,scinot.size()-1);
    scinot.erase(1,1);
    int zeros_to_add = scipow-scinot.size()+1;
    for (int i = 0; i < zeros_to_add; i++) scinot += '0';
    return scinot;
}

/* Lee una única linea (string) del .csv y la traduce a la clase ``userdata``, asignando cada "entrada" de la fila a una variable de la clase.
*/
userdata read_row_values(std::string row) 
{
    int cell_start_idx = 0;
    int cell_end_idx;
    int row_length = row.size();

    // Objeto donde se guardarán los datos del usuario
    userdata row_values;

    for (int col = 0; col < CSV_NUM_COLUMNS; col++) {
        // Se construye una substring auxiliar que contiene todos los datos de la fila que no se han procesado aún. (en la iteración 0 substring es igual a row, en la iteración 1 substring contiene toda la fila excepto universidad, etc.)
        std::string substring = row.substr(cell_start_idx, row_length-cell_start_idx);

        if (substring.find(',') == std::string::npos) {
            cell_end_idx = row_length;
        }

        // Si encuentra una coma, se reasigna el índice donde termina el dato actual, al índice de la primera coma que se encontró.
        else {
            cell_end_idx = cell_start_idx + substring.find(',');
        }
        std::string data_cell = row.substr(cell_start_idx,cell_end_idx-cell_start_idx);

        // Revisar si el dato leído contiene notacion cientifica, de ser así, convertirlo a un unsigned long long int.
        if (data_cell.find("E+") != std::string::npos) {
            data_cell = SciNot_to_ull(data_cell);
        }

        // Inicializar valores del objeto ``userdata`` a partir de los datos (ingresados a init_from_str en formato std::string) de la fila.
        row_values.init_from_str(col, data_cell);
        cell_start_idx = cell_end_idx+1;
    }
    return row_values;
}

/* Lee N filas del .csv y devuelve un vector con "structs usuario", donde cada struct contiene a todos los datos de una fila asociados a un mismo usuario.
*/
std::vector<userdata> csv_to_vector(std::ifstream& file, size_t n_rows) 
{
    if (_PARSE_DEBUG) std::cout << "Storing csv rows in vector... ";

    std::vector<userdata> vec;
    size_t rows_read = 0;
    std::string row_string;

    // Esto es solo para saltar la primera linea del .csv, que solo contiene una fila con los "nombres" de los datos
    std::getline(file, row_string);

    // Leer líneas hasta alcanzar las N líneas solicitadas
    while (rows_read < n_rows) {

        std::getline(file,row_string);
        userdata row_data = read_row_values(row_string);

        // Pushear nuevo usuario al vector de usuarios que se devolverá.
        vec.push_back(row_data);
        rows_read++;
    }

    if (_PARSE_DEBUG) std::cout << "done" << std::endl;
    return vec;
}

};

#endif