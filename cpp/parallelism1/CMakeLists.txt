cmake_minimum_required(VERSION 3.31)
project(parallelism1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(parallelism1 main.cpp)
