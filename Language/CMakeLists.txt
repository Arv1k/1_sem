cmake_minimum_required(VERSION 3.12)
project(Language)

set(CMAKE_CXX_STANDARD 14)

add_executable(Language main.cpp language.h language.cpp
                        ../make_enc/enc.h ../make_enc/enc.cpp
                        tree/binary_tree.cpp tree/binary_tree.h)