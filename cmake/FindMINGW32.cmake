find_path(MINGW32_INCLUDE
        NAMES memory.h
        PATHS
        C:/MinGW/include
        C:/MinGW/x86_64-w64-mingw32/include)
find_library(MINGW32_LIB mingw32
        PATHS
        C:/MinGW/lib
        C:/MinGW/x86_64-w64-mingw32/lib)

#include_directories(${MINGW32_INCLUDE})