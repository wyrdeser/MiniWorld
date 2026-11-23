cmake_minimum_required(VERSION 3.20)
project(MiniWorld LANGUAGES C CXX)

find_package(SDL3 REQUIRED CONFIG)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(glad STATIC third_party/glad/src/gl.c)
target_include_directories(glad PUBLIC third_party/glad/include)

add_executable(
    MiniWorld
    src/main.cpp

)

target_compile_options(MiniWorld PRIVATE -Wall -Wextra)

target_include_directories(MiniWorld PRIVATE
    src
    third_party/stb
    third_party/glm
)

target_link_libraries(MiniWorld PRIVATE SDL3::SDL3 glad)
