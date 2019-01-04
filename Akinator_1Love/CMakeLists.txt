cmake_minimum_required(VERSION 3.12)
project(Akinator_1Love)

set(CMAKE_CXX_STANDARD 14)

add_executable(Akinator_1Love main.cpp akinator.h tree/binary_tree.h tree/binary_tree.cpp akinator.cpp)