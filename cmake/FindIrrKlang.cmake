#Includes GLAD, GLM and linkes MINGW OpenGL library

find_path(IRRKLANG_INCLUDE
        NAMES irrKlang.h
        PATHS
        C:/Libraries/irrKlang/include)

find_library(IRRKLANG_LIB irrKlang
        PATHS
        C:/Libraries/irrKlang/lib/Winx86-gcc)

include_directories(${IRRKLANG_INCLUDE})