//
// Created by fin on 30.01.19.
//

#include <stdio.h>
#include "test.h"
#include "../kernel/gc.h"
#include "../kernel/stack_frame.h"
#include "../vm.h"

test_result_t test_project_div_i() {
    start("test_project_div_i.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 3 &&
        frame->work_stack[frame->index_first_element_work_stack - 1] == 3) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_add() {
    start("test_project_add.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 16) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_mul() {
    start("test_project_mul.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 20) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_compare_1() {
    start("test_project_compare_1.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 0) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_compare_2() {
    start("test_project_compare_2.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 7) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_invoke() {
    start("test_project_invoke.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 21) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_class() {
    start("test_project_class.fn");

    frame_t *frame = find_frame("main()");

    if (frame->work_stack[frame->index_first_element_work_stack] == 28) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_gc() {
    start("test_project_gc.fn");

    if (get_gc()->number_objects == 3) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_gc_tree_1() {
    start("test_project_gc_tree_1.fn");

    if (get_gc()->number_objects == 2) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_project_gc_tree_2() {
    start("test_project_gc_tree_2.fn");

    if (get_gc()->number_objects == 1) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

int main() {
    int number_test_functions = 10;
    test_result_t(*test_functions[number_test_functions])();
    test_functions[0] = test_project_div_i;
    test_functions[1] = test_project_add;
    test_functions[2] = test_project_mul;
    test_functions[3] = test_project_compare_1;
    test_functions[4] = test_project_compare_2;
    test_functions[5] = test_project_invoke;
    test_functions[6] = test_project_class;
    test_functions[7] = test_project_gc;
    test_functions[8] = test_project_gc_tree_1;
    test_functions[9] = test_project_gc_tree_2;

    char *name_test_functions[number_test_functions];
    name_test_functions[0] = "test_project_div_i():";
    name_test_functions[1] = "test_project_add():";
    name_test_functions[2] = "test_project_mul():";
    name_test_functions[3] = "test_project_compare_1():";
    name_test_functions[4] = "test_project_compare_2():";
    name_test_functions[5] = "test_project_invoke():";
    name_test_functions[6] = "test_project_class():";
    name_test_functions[7] = "test_project_gc():";
    name_test_functions[8] = "test_project_gc_tree_1():";
    name_test_functions[9] = "test_project_gc_tree_2():";

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