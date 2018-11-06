CC=g++

all: cpu

cpu: main.o cpu.o enc.o stack.o
    $(CC) -o cpu main.o cpu.o enc.o stack.o

main.o: cpu.o main.cpp
    $(CC) -c -o main.o main.cpp enc.o stack.o enc.o

cpu.o: enc.o stack.o CPU.cpp
    $(CC) -c -o cpu.o CPU.cpp enc.o stack.o

enc.o: enc_dir/enc.cpp
    $(CC) -c -o enc.o enc_dir/enc.cpp

stack.o: stack_dir/stack.cpp
    $(CC) -c -o stack.o stack_dir/stack.cpp
