cmake_minimum_required(VERSION 3.12)
project(Differentiator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Differentiator main.cpp differ.cpp differ.h
                              tree/binary_tree.h tree/binary_tree.cpp com.h)