cmake_minimum_required(VERSION 3.23)

project(XIRC)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/headers")

add_executable(xirc)

target_sources(xirc
PRIVATE
    src/main.cpp
    src/headers/connection.hpp
    src/headers/style.hpp
    src/code/style.cpp
    src/code/connection.cpp
)