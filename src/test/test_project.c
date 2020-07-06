//
// Created by fin on 30.01.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "../main/kernel/gc.h"
#include "../main/kernel/stack_frame.h"
#include "../main/vm.h"

enum test_result test_project_div_i() {
    start("src/test/compile_source/test_project_div_i.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 3 &&
        frame->work_stack[frame->index_first_element_work_stack - 1] == 3) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_add() {
    start("src/test/compile_source/test_project_add.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 16) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_mul() {
    start("src/test/compile_source/test_project_mul.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 20) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_compare_1() {
    start("src/test/compile_source/test_project_compare_1.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 0) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_compare_2() {
    start("src/test/compile_source/test_project_compare_2.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 7) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_invoke() {
    start("src/test/compile_source/test_project_invoke.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 21) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_invoke_2() {
    start("src/test/compile_source/test_project_invoke_2.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 21) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_class() {
    start("src/test/compile_source/test_project_class.fn");

    struct frame *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 28) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_gc() {
    start("src/test/compile_source/test_project_gc.fn");

    if (get_gc()->number_objects == 3) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_gc_tree_1() {
    start("src/test/compile_source/test_project_gc_tree_1.fn");

    if (get_gc()->number_objects == 2) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_gc_tree_2() {
    start("src/test/compile_source/test_project_gc_tree_2.fn");

    if (get_gc()->number_objects == 1) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

enum test_result test_project_loop() {
    start("src/test/compile_source/test_project_loop.fn");

    if (get_stack_frame()->frames[0]->local_pool[2] == 20) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

int main() {
    int number_test_functions = 12;
    enum test_result(*test_functions[number_test_functions])();
    test_functions[0] = test_project_div_i;
    test_functions[1] = test_project_add;
    test_functions[2] = test_project_mul;
    test_functions[3] = test_project_compare_1;
    test_functions[4] = test_project_compare_2;
    test_functions[5] = test_project_invoke;
    test_functions[6] = test_project_invoke_2;
    test_functions[7] = test_project_class;
    test_functions[8] = test_project_gc;
    test_functions[9] = test_project_gc_tree_1;
    test_functions[10] = test_project_gc_tree_2;
    test_functions[11] = test_project_loop;

    char *name_test_functions[number_test_functions];
    name_test_functions[0] = "test_project_div_i():";
    name_test_functions[1] = "test_project_add():";
    name_test_functions[2] = "test_project_mul():";
    name_test_functions[3] = "test_project_compare_1():";
    name_test_functions[4] = "test_project_compare_2():";
    name_test_functions[5] = "test_project_invoke():";
    name_test_functions[6] = "test_project_invoke_2():";
    name_test_functions[7] = "test_project_class():";
    name_test_functions[8] = "test_project_gc():";
    name_test_functions[9] = "test_project_gc_tree_1():";
    name_test_functions[10] = "test_project_gc_tree_2():";
    name_test_functions[11] = "test_project_loop():";

    for (int i = 0; i < number_test_functions; ++i) {
        puts(name_test_functions[i]);
        if (test_functions[i]() == TEST_SUCCESS) {
            puts("Test passed successfully\n");
            fflush(stdout);
        } else {
            fputs("Test failed\n", stderr);
            fflush(stderr);
            exit(0);
        }
        puts("-----------------------------------");
    }

    destructor_stack_frame();
    destructor_gc();

    return 0;
}