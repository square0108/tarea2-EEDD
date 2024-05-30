#include "parsing_struct.h"
#include "map_ADT.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <type_traits>

#define CSV_NUM_COLUMNS 7
#define CSV_NUM_ENTRIES 21070

// Modifica una string de notación científica a forma decimal (no cambia tipo de dato)
// nota: esta funcion destruye la string de entrada
std::string SciNot_to_ull(std::string& scinot) {
    int plus_idx = scinot.find('+');
    int scipow = std::stoi(scinot.substr(plus_idx,scinot.size()-plus_idx));
    scinot.erase(plus_idx-1,scinot.size()-1);
    scinot.erase(1,1);
    int zeros_to_add = scipow-scinot.size()+1;
    for (int i = 0; i < zeros_to_add; i++) scinot += '0';
    return scinot;
}

namespace udec {

twtdata read_row_values(std::string row) 
{
    int cell_start_idx = 0;
    twtdata row_values;
    int cell_end_idx;
    int row_length = row.size();

    for (int col = 0; col < CSV_NUM_COLUMNS; col++) {
        std::string substring = row.substr(cell_start_idx,row_length-cell_start_idx);
        if (substring.find(',') == std::string::npos) {
            cell_end_idx = row_length;
        }
        else {
            cell_end_idx = cell_start_idx + substring.find(',');
        }
        std::string line_member = row.substr(cell_start_idx,cell_end_idx-cell_start_idx);
        if (line_member.find("E+") != std::string::npos) { // revisar si el sub-string leido en la fila contiene notacion cientifica. Esto podría moverse fuera del for loop.
            line_member = SciNot_to_ull(line_member);
        }
        row_values.init_from_str(col, line_member);
        cell_start_idx = cell_end_idx+1;
    }
}

void insert_lines(std::ifstream& file, MapADT<std::string,twtdata>& map, size_t n_parses) 
{
    std::string line; // almacena la fila que se lee en cada iteración
    std::getline(file,line); // para saltarse la primera fila
    size_t line_count = 0; // numero de filas leidas
    double total_running_time = 0;

    while (line_count < n_parses) {
        std::getline(file,line);
        twtdata row_values;
        int idx = 0;
        int line_sz = line.size();

        for (int col = 0; col < CSV_NUM_COLUMNS; col++) {
            std::string substring = line.substr(idx,line_sz-idx);
            int end_idx;
            if (substring.find(',') == std::string::npos) {
                end_idx = line_sz;
            }
            else {
                end_idx = idx+substring.find(',');
            }
            std::string line_member = line.substr(idx,end_idx-idx);
            if (line_member.find("E+") != std::string::npos) { // revisar si el sub-string leido en la fila contiene notacion cientifica. Esto podría moverse fuera del for loop.
                line_member = SciNot_to_ull(line_member);
            }
            row_values.init_from_str(col, line_member);
            idx = end_idx+1;
        }

        auto start = std::chrono::high_resolution_clock::now();
        map.put(row_values.username,row_values);
        auto end = std::chrono::high_resolution_clock::now();

        // Aqui se verifica el tipo de dato de la clave
        double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        running_time *= 1e-9;
        total_running_time += running_time;

        line_count++;
    }
    std::cout << "username_hash" << ";" << n_parses << ";" << total_running_time << std::endl;
}

void insert_lines(std::ifstream& file, MapADT<unsigned long long int,twtdata>& map, size_t n_parses) 
{
    std::string line; // almacena la fila que se lee en cada iteración
    std::getline(file,line); // para saltarse la primera fila
    size_t line_count = 0; // numero de filas leidas
    double total_running_time = 0;

    while (line_count < n_parses) {
        std::getline(file,line);
        twtdata row_values;
        int idx = 0;
        int line_sz = line.size();

        for (int col = 0; col < CSV_NUM_COLUMNS; col++) {
            std::string substring = line.substr(idx,line_sz-idx);
            int end_idx;
            if (substring.find(',') == std::string::npos) {
                end_idx = line_sz;
            }
            else {
                end_idx = idx+substring.find(',');
            }
            /* debugging print */
            // std::cout << "col: " << col << " start_idx: " << idx << " end_idx: " << end_idx << std::endl;
            std::string line_member = line.substr(idx,end_idx-idx);
            if (line_member.find("E+") != std::string::npos) { // revisar si el sub-string leido en la fila contiene notacion cientifica. Esto podría moverse fuera del for loop.
                line_member = SciNot_to_ull(line_member);
            }
            row_values.init_from_str(col, line_member);
            idx = end_idx+1;
        }

        auto start = std::chrono::high_resolution_clock::now();
        map.put(row_values.user_id,row_values);
        auto end = std::chrono::high_resolution_clock::now();

        // Aqui se verifica el tipo de dato de la clave
        double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        running_time *= 1e-9;
        total_running_time += running_time;

        line_count++;
    }
    std::cout << "ID_hash" << ";" << n_parses << ";" << total_running_time << std::endl;
}

};