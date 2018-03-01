cmake_minimum_required(VERSION 3.9)
project(string_parsing_test)

set(CMAKE_CXX_STANDARD 17)

find_package( Boost REQUIRED)

set(CMAKE_CXX_FLAG '-march=native')

add_executable(string_parsing_test src/main.cpp)
