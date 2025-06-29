cmake_minimum_required(VERSION 3.31)
project(parallelism2)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI REQUIRED)

add_executable(parallelism2 main.cpp)

target_link_libraries(parallelism2 PUBLIC MPI::MPI_CXX)
