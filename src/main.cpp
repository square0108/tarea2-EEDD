#include <iostream>
#include <fstream>
#include <parsing_struct.h>
#include <vector>
#include <string>
#include <math.h>
#include <open_hash.h>
#include <hash_functions.h>
#include <utility>

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

void parse_line(std::ifstream& file, std::vector<twtdata*>& TEMP_container, size_t n_parses) {
    std::string line; // almacena la fila que se lee en cada iteración
    std::getline(file,line); // para saltarse la primera fila
    size_t line_count = 0; // numero de filas leidas

    while (line_count < n_parses) {
        std::getline(file,line);
        twtdata* row_values = new twtdata;
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
            row_values->init_from_str(col, line_member);
            idx = end_idx+1;
        }
        TEMP_container.push_back(row_values);
        line_count++;
    }
}

int main()
{
    std::vector<twtdata*> userdata;
    std::ifstream stream;
    stream.open("universities_followers.csv", std::ifstream::in);
    parse_line(stream, userdata, CSV_NUM_ENTRIES);
    OpenHashTable<unsigned long long int,twtdata> poop(22000, CSandCompress);
    for (auto& user : userdata) {
        poop.put(user->user_id, *user);
    }
    for (auto& user : userdata) {
        poop.get(user->user_id);
    }

    stream.close();
    return 0;
}
