//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_FILER_HANDLER_H
#define MINALEAR_FILER_HANDLER_H

#include <fstream>

namespace minalear {
    const char *readFile(const char *filename);
    const char *readBinaryFile(const char *filename);
}

#endif //MINALEAR_FILER_HANDLER_H
