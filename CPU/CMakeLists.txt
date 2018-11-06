cmake_minimum_required(VERSION 3.12)
project(CPU)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPU main.cpp CPU.h  CPU.cpp
                   enc_dir/enc.h enc_dir/enc.cpp
                   stack_dir/stack.cpp stack_dir/stack.h stack_dir/Unittests.cpp)