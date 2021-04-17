cmake_minimum_required(VERSION 3.19)
project(lexer)

set(CMAKE_CXX_STANDARD 20)

add_executable(lexer src/main.cpp src/automata.cpp include/automata.hpp)