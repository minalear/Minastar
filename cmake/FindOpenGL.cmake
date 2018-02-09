#Includes GLAD, GLM and linkes MINGW OpenGL library

find_path(GLAD_INCLUDE
        NAMES glad/glad.h
        PATHS
        C:/Libraries/GLAD/include
        C:/Libraries/OpenGL/GLAD/include)

find_path(GLM_INCLUDE
        NAMES glm.hpp
        PATHS
        C:/Libraries/OpenGL/GLM/glm)

find_library(OPENGL_LIB opengl32
        PATHS
        C:/MinGW/lib)

include_directories(${GLAD_INCLUDE})
include_directories(${GLM_INCLUDE})