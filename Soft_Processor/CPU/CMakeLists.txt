cmake_minimum_required(VERSION 3.12)
project(CPU)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPU main.cpp cpu.cpp cpu.h
                   stack_dir/stack.cpp stack_dir/stack.h
                   ../commands.h)