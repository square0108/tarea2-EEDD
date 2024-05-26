#include <iostream>
#include <fstream>
#include <parsing_struct.h>
#include <vector>
#include <string>
#include <math.h>

std::string SciNot_to_ull(std::string& scinot) {
    // nota: esta funcion destruye la string de entrada
    int plus_idx = scinot.find('+');
    int scipow = std::stoi(scinot.substr(plus_idx,scinot.size()-plus_idx));
    scinot.erase(plus_idx-1,scinot.size()-1);
    scinot.erase(1,1);
    int zeros_to_add = scipow-scinot.size()+1;
    for (int i = 0; i < zeros_to_add; i++) scinot += '0';
    return scinot;
}

void parse_line(std::ifstream& file, std::vector<uniflw_values*>& container, size_t n_parses) {
    std::string line;
    std::getline(file,line); // skip first line
    size_t line_count = 0;

    while (line_count < n_parses) {
        std::getline(file,line);
        uniflw_values* line_values = new uniflw_values;
        int idx = 0;
        int line_sz = line.size();

        for (int col = 0; col < 7; col++) {
            std::string substring = line.substr(idx,line_sz-idx);
            int end_idx;
            if (substring.find(',') == std::string::npos) {
                end_idx = line_sz;
            }
            else {
                end_idx = idx+substring.find(',');
            }
            /* std::cout << "col: " << col << " start_idx: " << idx << " end_idx: " << end_idx << std::endl;
            *   debugging print
            */
            std::string value_member = line.substr(idx,end_idx-idx);
            if (value_member.find("E+") != std::string::npos) {
                value_member = SciNot_to_ull(value_member);
            }
            line_values->init_from_str(col, value_member);
            idx = end_idx+1;
        }
        container.push_back(line_values);
        line_count++;
    }
}

int main(int argc, char *argv[])
{
    std::vector<uniflw_values*> userdata;
    std::ifstream stream;
    stream.open("universities_followers.csv", std::ifstream::in);
    parse_line(stream, userdata, 4);
    for (auto& v : userdata) v->print_data();

    stream.close();
    return 0;
}
