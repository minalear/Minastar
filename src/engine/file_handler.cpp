//
// Created by Trevor Fisher on 1/19/2018.
//

#include "file_handler.h"

const char* minalear::read_file(const char *filename) {
    std::fstream file(filename);

    std::string line, output;
    while (getline(file, line)) {
        output += line + "\n";
    }

    char* source = new char[output.size() + 1];
    for (int i = 0; i < output.size(); i++) {
        source[i] = output[i];
    }
    source[output.size()] = '\0';

    file.close();
    return source;
}

const char* minalear::read_binary_file(const char *filename, uint32_t &file_size) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::end);
    file_size = (uint32_t)file.tellg();
    file.seekg(0, std::ios::beg);

    char* data = new char[file_size];
    file.read(data, file_size);

    file.close();
    return data;
}