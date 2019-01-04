cmake_minimum_required(VERSION 3.12)
project(Assembler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assembler main.cpp assembler.cpp assembler.h
                         enc_dir/enc.cpp enc_dir/enc.h
                         ../commands.h ../DSL.h)