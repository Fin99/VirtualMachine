cmake_minimum_required(VERSION 3.12)
project(VirtualMachine C)

set(CMAKE_CXX_STANDARD 14)

add_executable(VirtualMachine vm.h vm.c parsing-bytecode/loader.h parsing-bytecode/loader.c instruction.h instruction.c parsing-bytecode/string.c parsing-bytecode/string.h parsing-bytecode/file.c parsing-bytecode/file.h test/test_parsing.c test/test_parsing.h test/test.h)