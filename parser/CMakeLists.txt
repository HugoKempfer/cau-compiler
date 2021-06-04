cmake_minimum_required(VERSION 3.19)
project(parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(parser main.cpp symbols_types.cpp include/symbols_types.h)