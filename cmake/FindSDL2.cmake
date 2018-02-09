find_path(SDL2_INCLUDE
        NAMES SDL2/SDL.h
        PATHS
        C:/Libraries/SDL2/x86/include)

find_library(SDL2_LIB sdl2
        PATHS
        C:/Libraries/SDL2/x86/lib)
find_library(SDL2_MAIN_LIB sdl2main
        PATHS
        C:/Libraries/SDL2/x86/lib)

include_directories(${SDL2_INCLUDE})