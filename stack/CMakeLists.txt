cmake_minimum_required(VERSION 3.12)
project(stack)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -fsanitize=address)
add_executable(stack main.cpp stack.h stack.cpp)