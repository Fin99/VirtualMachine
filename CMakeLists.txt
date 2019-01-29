cmake_minimum_required(VERSION 3.12)
project(VirtualMachine C)

set(CMAKE_CXX_STANDARD 14)

set(Parser
        parsing-bytecode/string.c parsing-bytecode/string.h
        parsing-bytecode/file.c parsing-bytecode/file.h parsing-bytecode/pars_element.c parsing-bytecode/pars_element.h parsing-bytecode/parser.c parsing-bytecode/parser.h)

set(Kernel kernel/instruction.h kernel/instruction.c
        kernel/stack_frame.h kernel/stack_frame.c
        kernel/frame.h kernel/frame.c kernel/class.c kernel/class.h kernel/gc.h kernel/gc.c)

set(TestParser test/test.h
        test/test_parsing.h test/test_parsing.c)
set(TestKernel test/test.h
        test/test_kernel.c test/test_kernel.h)


add_executable(TestParser ${TestParser} ${Parser})

add_executable(TestKernel ${TestKernel} ${Kernel})
