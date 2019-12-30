//
// Created by fin on 30.01.19.
//

#include "vm.h"
#include "kernel/gc.h"
#include "kernel/stack_frame.h"
#include "parsing/bytecode/parser.h"

void start(char *file_name) {
    init_gc();
    init_stack_frame();

    load_class_and_frame(file_name);

    get_stack_frame()->stack_frame[++get_stack_frame()->index_first_element_stack_frame] = find_frame("main()");

    execute_frame(find_frame("main()"));
//
//    destructor_gc();
//    destructor_stack_frame();
}