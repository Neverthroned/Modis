cmake_minimum_required(VERSION 3.20)
project(Modis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)

add_executable(Modis src/main.cpp external/glad/src/gl.c application/application.cpp)

target_include_directories(Modis PRIVATE external/glad/include external/stb application)

target_link_libraries(Modis PRIVATE SDL3::SDL3)