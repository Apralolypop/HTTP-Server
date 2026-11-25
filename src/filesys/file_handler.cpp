#include "file_handler.h"
#include <fstream>
#include <sstream>

std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);

    if(!file.is_open()) {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}