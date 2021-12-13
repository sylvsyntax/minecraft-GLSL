cmake_minimum_required(VERSION 3.21)
project(minecraft_GLSL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:\\Users\\miste\\Documents\\vcpkg\\packages\\")
set(SOURCE_FILES src/main.cpp src/glad.c src/Block.cpp src/Camera.cpp src/Chunk.cpp src/Cube.cpp src/EBO.cpp src/Mesh.cpp src/shaderClass.cpp src/shapes.cpp src/stb.cpp src/Texture.cpp src/VAO.cpp src/VBO.cpp src/World.cpp src/PerlinNoise.cpp src/PerlinNoise.h)
include_directories(src)
include_directories(Libraries/include)

add_executable(minecraft_GLSL ${SOURCE_FILES})
set_property(TARGET minecraft_GLSL PROPERTY C_STANDARD 17)
find_package(glm CONFIG REQUIRED)
target_link_libraries(minecraft_GLSL PRIVATE glm::glm)


find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    message("opengl found")
    message("include dir: ${OPENGL_INCLUDE_DIR}")
    message("link libraries: ${OPENGL_gl_LIBRARY}")
else (OPENGL_FOUND)
    message("opengl not found")
endif()

target_link_libraries(minecraft_GLSL PRIVATE ${OPENGL_gl_LIBRARY})


find_package(glad CONFIG REQUIRED)
target_link_libraries(minecraft_GLSL PRIVATE glad::glad)

target_link_libraries(minecraft_GLSL PRIVATE gdi32)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(minecraft_GLSL PRIVATE glfw)