cmake_minimum_required(VERSION 3.9)
project(sinistar)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

file(GLOB SOURCE_FILES src/*.cpp src/*.h)
file(GLOB SHADER_FILES shaders/*.glsl)
file(GLOB RESOURCE_FILES textures/*.png)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/textures)
file(COPY ${SHADER_FILES} DESTINATION ${PROJECT_BINARY_DIR}/shaders)
file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/textures)

find_package(MINGW32 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(SOURCE_FILES ${SOURCE_FILES} C:/Libraries/OpenGL/GLAD/src/glad.c src/game_entity.cpp src/game_entity.h src/asteroid.cpp src/asteroid.h)

add_executable(sinistar ${SOURCE_FILES})
target_link_libraries(sinistar ${MINGW32_LIB} ${SDL2_MAIN_LIB} ${SDL2_LIB} ${OPENGL_LIB})

add_custom_command(
        TARGET sinistar POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Libraries/SDL2/x86/bin/SDL2.dll"
        $<TARGET_FILE_DIR:sinistar>
)