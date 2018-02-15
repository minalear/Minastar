//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_FILER_HANDLER_H
#define MINALEAR_FILER_HANDLER_H

#include <fstream>

namespace minalear {
    const char *read_file(const char *filename);
    const char *read_binary_file(const char *filename, uint32_t &file_size);
}

#endif //MINALEAR_FILER_HANDLER_H
