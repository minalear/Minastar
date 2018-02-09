find_path(MINGW32_INCLUDE
        NAMES memory.h
        PATHS
        C:/MinGW/include)
find_library(MINGW32_LIB mingw32
        PATHS
        C:/MinGW/lib)

#include_directories(${MINGW32_INCLUDE})