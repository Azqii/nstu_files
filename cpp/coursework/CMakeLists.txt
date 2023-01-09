cmake_minimum_required(VERSION 3.24)
project(crs)

set(CMAKE_CXX_STANDARD 17)

add_executable(crs main.cpp DateTime.cpp DateTime.h Rental.cpp Rental.h LinkedList.h)
