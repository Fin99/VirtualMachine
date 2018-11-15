cmake_minimum_required(VERSION 3.12)
project(VM)

set(CMAKE_CXX_STANDARD 14)

add_executable(VM vm/VM.h vm/VM.c vm/ConstantPool.h vm/Frame.h vm/parsing_bytecode/Loader.h vm/parsing_bytecode/Loader.c vm/Instruction.h vm/Frame.c vm/Instruction.c vm/parsing_bytecode/String.c vm/parsing_bytecode/String.h vm/parsing_bytecode/File.c vm/parsing_bytecode/File.h)