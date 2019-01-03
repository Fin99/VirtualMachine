cmake_minimum_required(VERSION 3.12)
project(VirtualMachine C)

set(CMAKE_CXX_STANDARD 14)

set(Parser parsing-bytecode/loader.h parsing-bytecode/loader.c
        parsing-bytecode/string.c parsing-bytecode/string.h
        parsing-bytecode/file.c parsing-bytecode/file.h)

set(Kernel instruction.h instruction.c
        stack_frame.h stack_frame.c
        frame.h frame.c)

set(Test test/test.h
        test/test_parsing.h test/test_parsing.c)

add_executable(VirtualMachine ${Parser} ${Kernel} ${Test})
