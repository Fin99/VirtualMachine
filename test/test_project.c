//
// Created by fin on 30.01.19.
//

#include <stdbool.h>
#include <stdio.h>
#include "test.h"
#include "../parsing-bytecode/parser.h"
#include "../kernel/gc.h"
#include "../kernel/stack_frame.h"

test_result_t test_parser() {
    init_gc();
    init_stack_frame();
    load_class_and_frame("SumTest.fn");


    get_stack_frame()->stack_frame[++get_stack_frame()->index_first_element_stack_frame] = get_stack_frame()->frames[0];

    execute_frame(get_stack_frame()->frames[0]);
    if (get_gc()->number_objects == 1) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

int main() {
    int number_test_functions = 1;
    test_result_t(*test_functions[number_test_functions])();
    test_functions[0] = test_parser;

    char *name_test_functions[number_test_functions];
    name_test_functions[0] = "test_parser():";

    for (int i = 0; i < number_test_functions; ++i) {
        puts(name_test_functions[i]);
        if (test_functions[i]() == TEST_SUCCESS) {
            puts("Test passed successfully\n");
            fflush(stdout);
        } else {
            fputs("Test failed\n", stderr);
            fflush(stderr);
        }
        puts("-----------------------------------");
    }

    destructor_stack_frame();
    destructor_gc();

    return 0;
}