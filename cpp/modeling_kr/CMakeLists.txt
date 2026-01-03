cmake_minimum_required(VERSION 3.10)
project(modeling_kr)

set(CMAKE_CXX_STANDARD 17)

add_executable(modeling_kr
        main.cpp
        globals.cpp
        Client.cpp
        Clerk.cpp
        Shop.cpp)
