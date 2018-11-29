cmake_minimum_required(VERSION 3.12)
project(VM)

set(CMAKE_CXX_STANDARD 14)

add_executable(VM vm/VM.h vm/VM.c vm/frame.h vm/parsing_bytecode/loader.h vm/parsing_bytecode/loader.c vm/instruction.h vm/frame.c vm/instruction.c vm/parsing_bytecode/string.c vm/parsing_bytecode/string.h vm/parsing_bytecode/file.c vm/parsing_bytecode/file.h)