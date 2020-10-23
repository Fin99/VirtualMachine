cmake_minimum_required(VERSION 3.12)
project(VirtualMachine C)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB_RECURSE parser_source "src/main/compiler/source/*")
FILE(GLOB_RECURSE parser_bytecode "src/main/compiler/bytecode/*")
FILE(GLOB_RECURSE parser_commons "src/main/compiler/commons/*")
FILE(GLOB_RECURSE kernel "src/main/kernel/*")

set(ParserBytecode ${parser_bytecode} ${parser_commons})
set(ParserSource ${parser_source} ${parser_commons})

set(Kernel ${kernel})

set(Project ${ParserBytecode} ${ParserSource} ${Kernel} src/main/vm.c src/main/vm.h)

set(TestKernel src/test/test.h src/test/test_kernel.c ${Kernel})
set(TestParser src/test/test.h src/test/test_compile_source.c ${ParserSource})
set(TestProject src/test/test.h src/test/test_project.c ${Project})

add_executable(test_kernel ${TestKernel})

add_executable(test_parser ${TestParser})

add_executable(test_project ${TestProject})
