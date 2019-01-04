cmake_minimum_required(VERSION 3.12)
project(make_enc)

set(CMAKE_CXX_STANDARD 14)

add_executable(make_enc main.cpp enc.cpp enc.h)