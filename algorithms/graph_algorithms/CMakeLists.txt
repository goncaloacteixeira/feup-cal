cmake_minimum_required(VERSION 3.15)
project(graph-algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(graph-algorithms main.cpp Graph.h Visitation.h path_finders.h lib/fort.c lib/fort.h lib/fort.hpp)