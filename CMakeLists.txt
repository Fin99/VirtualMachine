cmake_minimum_required(VERSION 3.12)
project(VirtualMachine C)

set(CMAKE_CXX_STANDARD 14)

set(Parser
        src/main/parsing/bytecode/string.c src/main/parsing/bytecode/string.h
        src/main/parsing/bytecode/file.c src/main/parsing/bytecode/file.h src/main/parsing/bytecode/pars_element.c src/main/parsing/bytecode/pars_element.h
        src/main/parsing/bytecode/parser.c src/main/parsing/bytecode/parser.h)

set(Kernel src/main/kernel/instruction.h src/main/kernel/instruction.c
        src/main/kernel/stack_frame.h src/main/kernel/stack_frame.c
        src/main/kernel/frame.h src/main/kernel/frame.c src/main/kernel/class.c src/main/kernel/class.h src/main/kernel/gc.h src/main/kernel/gc.c)

set(Project ${Parser} ${Kernel} src/main/vm.c src/main/vm.h)

set(TestKernel src/test/test.h src/test/test_kernel.c ${Kernel})
set(TestProject src/test/test.h src/test/test_project.c src/test/test_project.h ${Project})

add_executable(test_kernel ${TestKernel})

add_executable(test_project ${TestProject})
