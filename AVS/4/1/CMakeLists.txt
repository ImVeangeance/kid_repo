cmake_minimum_required(VERSION 3.15)
project(1)

set(CMAKE_CXX_STANDARD 17)

#set(my_comp_flags "-pg")

set(CMAKE_CXX_FLAGS "-pg")

add_executable(1 main.cpp)