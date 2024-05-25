#include <iostream>
#include <fstream>
#include <parsing_struct.h>
#include <vector>
#include <string>

void read_line(std::ifstream& file) {
    std::string line;
    std::getline(file,line);
    int lines_read = 0;
    int lines_to_read = 5;
    while (std::getline(file,line)) {
        if (lines_read >= lines_to_read) break;
        std::cout << line << std::endl;
        lines_read++;
    }

}

int main(int argc, char *argv[])
{
    std::ifstream stream;
    stream.open("universities_followers.csv", std::ifstream::in);
    std::cout << "Stream is open? : " << stream.is_open() << std::endl;
    read_line(stream);

    return 0;
}
