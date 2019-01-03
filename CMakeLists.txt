cmake_minimum_required(VERSION 3.12)
project(VM)

set(CMAKE_CXX_STANDARD 14)

add_executable(VM vm.h vm.c parsing_bytecode/loader.h parsing_bytecode/loader.c instruction.h instruction.c parsing_bytecode/string.c parsing_bytecode/string.h parsing_bytecode/file.c parsing_bytecode/file.h)