//
// Created by Trevor Fisher on 1/19/2018.
//

#include "filer_handler.h"

const char* minalear::readFile(const char* filename) {
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

const char* minalear::readBinaryFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::end);
    std::streampos filesize = file.tellg();
    file.seekg(0, std::ios::beg);

    char* data = new char[filesize];
    file.read(data, filesize);

    file.close();
    return data;
}