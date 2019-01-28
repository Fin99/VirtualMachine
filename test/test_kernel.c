#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "../kernel/frame.h"
#include "../kernel/stack_frame.h"
#include "../kernel/gc.h"

frame_t *create_test_frame_div_i() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 4;
    long long *args2 = malloc(sizeof(long long));
    args2[0] = 15;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, CONST, args2);
    instruction_t *instruction3 = constructor_instruction(2, DIV_I, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 4);
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = instruction3;
    instructions[3] = instruction4;

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 4);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_div_i() {
    init_stack_frame();

    frame_t *frame = create_test_frame_div_i();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 3 &&
        frame->work_stack[frame->index_first_element_work_stack - 1] == 3) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: const 4
    1: const 15
    2: div_i
    3: return
     */
}

frame_t *create_test_frame_add() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 12;
    long long *args2 = malloc(sizeof(long long));
    args2[0] = 4;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, CONST, args2);
    instruction_t *instruction3 = constructor_instruction(2, ADD, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 4);
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = instruction3;
    instructions[3] = instruction4;

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 4);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_add() {
    init_stack_frame();

    frame_t *frame = create_test_frame_add();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 16) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: const 12
    1: const 4
    2: add
    3: return
     */
}

frame_t *create_test_frame_mul() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 4;
    long long *args2 = malloc(sizeof(long long));
    args2[0] = 5;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, CONST, args2);
    instruction_t *instruction3 = constructor_instruction(2, MUL, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 4);
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = instruction3;
    instructions[3] = instruction4;

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 4);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_mul() {
    init_stack_frame();

    frame_t *frame = create_test_frame_mul();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 20) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: const 4
    1: const 5
    2: mul
    3: return
     */
}

frame_t *create_test_frame_compare_1() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 7;
    long long *args2 = malloc(sizeof(long long));
    args2[0] = 7;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, CONST, args2);
    instruction_t *instruction3 = constructor_instruction(2, COMPARE, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 4);
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = instruction3;
    instructions[3] = instruction4;

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 4);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_compare_1() {
    init_stack_frame();

    frame_t *frame = create_test_frame_compare_1();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 0) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: const 7
    1: const 7
    2: compare
    3: return
     */
}

frame_t *create_test_frame_compare_2() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 7;
    long long *args2 = malloc(sizeof(long long));
    args2[0] = 14;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, CONST, args2);
    instruction_t *instruction3 = constructor_instruction(2, COMPARE, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 4);
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = instruction3;
    instructions[3] = instruction4;

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 4);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_compare_2() {
    init_stack_frame();

    frame_t *frame = create_test_frame_compare_2();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 7) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: const 7
    1: const 14
    2: compare
    3: return
     */
}

frame_t *create_test_frame_invoke() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 14;
    long long *args2 = malloc(sizeof(long long));
    args2[0] = 0;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, INVOKE, args2);
    instruction_t *instruction3 = constructor_instruction(2, ADD, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 4);
    instructions[0] = instruction1;
    instructions[1] = instruction2;
    instructions[2] = instruction3;
    instructions[3] = instruction4;

    frame_t *frame = constructor_frame(1, VOID_RETURN, instructions, 4);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

frame_t *create_test_frame_invoked() {
    long long *args1 = malloc(sizeof(long long));
    args1[0] = 7;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction4 = constructor_instruction(1, I_RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 2);
    instructions[0] = instruction1;
    instructions[1] = instruction4;

    frame_t *frame = constructor_frame(0, INT_RETURN, instructions, 2);
    frame->name = malloc(sizeof(char) * 2);
    strcpy(frame->name, "a");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_invoke() {
    init_stack_frame();

    create_test_frame_invoked();
    frame_t *frame = create_test_frame_invoke();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 21) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: const 14
    1: invoke a
    2: add
    3: return

    a()
    0: const 7
    1: i_return
     */
}

void create_test_class() {
    class_t *class = malloc(sizeof(class_t));
    class->number_fields = 1;
    class->index_class = 0;
    class->name = malloc(sizeof(char) * 5);
    strcpy(class->name, "Main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->classes[stack_frame->number_classes++] = class;

}

frame_t *create_test_frame_class() {
    long long *index_class_1 = malloc(sizeof(long long));
    index_class_1[0] = 0;

    long long *index_class_1_local_pool = malloc(sizeof(long long));
    index_class_1_local_pool[0] = 0;
    long long *index_class_1_local_pool_1 = malloc(sizeof(long long));
    index_class_1_local_pool_1[0] = 0;
    long long *index_class_1_local_pool_2 = malloc(sizeof(long long));
    index_class_1_local_pool_2[0] = 0;

    long long *number_field_class_1 = malloc(sizeof(long long));
    number_field_class_1[0] = 0;
    long long *number_field_class_1_1 = malloc(sizeof(long long));
    number_field_class_1_1[0] = 0;


    long long *index_class_2 = malloc(sizeof(long long));
    index_class_2[0] = 0;

    long long *index_class_2_local_pool = malloc(sizeof(long long));
    index_class_2_local_pool[0] = 1;
    long long *index_class_2_local_pool_1 = malloc(sizeof(long long));
    index_class_2_local_pool_1[0] = 1;
    long long *index_class_2_local_pool_2 = malloc(sizeof(long long));
    index_class_2_local_pool_2[0] = 1;

    long long *number_field_class_2 = malloc(sizeof(long long));
    number_field_class_2[0] = 0;
    long long *number_field_class_2_1 = malloc(sizeof(long long));
    number_field_class_2_1[0] = 0;

    long long *const_value_1 = malloc(sizeof(long long));
    const_value_1[0] = 9;
    long long *const_value_2 = malloc(sizeof(long long));
    const_value_2[0] = 19;

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 16);

    instructions[0] = constructor_instruction(0, NEW, index_class_1);
    instructions[1] = constructor_instruction(1, STORE, index_class_1_local_pool);
    instructions[2] = constructor_instruction(2, NEW, index_class_2);
    instructions[3] = constructor_instruction(3, STORE, index_class_2_local_pool);

    instructions[4] = constructor_instruction(4, CONST, const_value_1);
    instructions[5] = constructor_instruction(5, LOAD, index_class_1_local_pool_1);
    instructions[6] = constructor_instruction(6, SET_FIELD, number_field_class_1);

    instructions[7] = constructor_instruction(7, CONST, const_value_2);
    instructions[8] = constructor_instruction(8, LOAD, index_class_2_local_pool_1);
    instructions[9] = constructor_instruction(9, SET_FIELD, number_field_class_2);

    instructions[10] = constructor_instruction(10, LOAD, index_class_1_local_pool_2);
    instructions[11] = constructor_instruction(11, GET_FIELD, number_field_class_1_1);

    instructions[12] = constructor_instruction(12, LOAD, index_class_2_local_pool_2);
    instructions[13] = constructor_instruction(13, GET_FIELD, number_field_class_2_1);

    instructions[14] = constructor_instruction(14, ADD, NULL);
    instructions[15] = constructor_instruction(15, RETURN, NULL);

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 16);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_class() {
    init_stack_frame();
    init_gc();

    create_test_class();
    frame_t *frame = create_test_frame_class();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 28) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: new 0
    1: store 0
    2: new 0
    3: store 1

    4: const 9
    5: load 0
    6: set_field 0

    7: const 19
    8: load 1
    9: set_field 0

    10: load 0
    11: get_field 0

    12: load 1
    13: get_field 0

    12: add
    13: return
     */
}

frame_t *create_test_frame_gc() {
    int number_object = 6;
    int number_instructions = number_object + 1 + number_object / 2;

    instruction_t **instructions = malloc(sizeof(instruction_t *) * number_instructions);
    for (int i = 0; i < number_instructions - 1; ++i) {
        if (i % 3 == 1) {
            long long *index_class_1 = malloc(sizeof(long long));
            index_class_1[0] = 0;
            instructions[i] = constructor_instruction(i, NEW, index_class_1);
//            instructions[i] = constructor_instruction(i, POP, NULL);
        } else {
            long long *index_class_1 = malloc(sizeof(long long));
            index_class_1[0] = 0;
            instructions[i] = constructor_instruction(i, NEW, index_class_1);
        }
    }
    instructions[number_instructions - 1] = constructor_instruction(number_instructions - 1, RETURN, NULL);

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, number_instructions);
    frame->name = malloc(sizeof(char) * 5);
    strcpy(frame->name, "main");

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_gc() {
    init_stack_frame();
    init_gc();

    create_test_class();
    frame_t *frame = create_test_frame_gc();
    execute_frame(frame);

    if (frame->work_stack[frame->index_first_element_work_stack] == 28) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: new 0
    1: store 0
    2: new 0
    3: store 1

    4: const 9
    5: load 0
    6: set_field 0

    7: const 19
    8: load 1
    9: set_field 0

    10: load 0
    11: get_field 0

    12: load 1
    13: get_field 0

    12: add
    13: return
     */
}

int main() {
    int number_test_functions = 8;
    test_result_t(*test_functions[number_test_functions])();
    test_functions[0] = test_kernel_div_i;
    test_functions[1] = test_kernel_add;
    test_functions[2] = test_kernel_mul;
    test_functions[3] = test_kernel_compare_1;
    test_functions[4] = test_kernel_compare_2;
    test_functions[5] = test_kernel_invoke;
    test_functions[6] = test_kernel_class;
    test_functions[7] = test_kernel_gc;

    char *name_test_functions[number_test_functions];
    name_test_functions[0] = "test_kernel_div_i():";
    name_test_functions[1] = "test_kernel_add():";
    name_test_functions[2] = "test_kernel_mul():";
    name_test_functions[3] = "test_kernel_compare_1():";
    name_test_functions[4] = "test_kernel_compare_2():";
    name_test_functions[5] = "test_kernel_invoke():";
    name_test_functions[6] = "test_kernel_class():";
    name_test_functions[7] = "test_kernel_gc():";

    for (int i = 0; i < number_test_functions; ++i) {
        puts(name_test_functions[i]);
        if (test_functions[i]() == TEST_SUCCESS) {
            puts("Test passed successfully\n");
            fflush(stdout);
        } else {
            fputs("Test failed\n", stderr);
            fflush(stderr);
        }
    }

    destructor_stack_frame();
    destructor_gc();

    return 0;
}