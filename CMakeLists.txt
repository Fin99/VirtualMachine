cmake_minimum_required(VERSION 3.12)
project(VM)

set(CMAKE_CXX_STANDARD 14)

add_executable(VM vm/VM.h vm/VM.c vm/ConstantPool.h vm/Frame.h vm/Loader.h vm/Loader.c vm/Instruction.h)