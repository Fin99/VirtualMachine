//
// Created by fin on 03.01.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "test_kernel.h"
#include "test.h"
#include "../frame.h"
#include "../stack_frame.h"

frame_t *create_test_frame_div_i() {
    int *args1 = malloc(sizeof(int));
    args1[0] = 4;
    int *args2 = malloc(sizeof(int));
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
    int *args1 = malloc(sizeof(int));
    args1[0] = 12;
    int *args2 = malloc(sizeof(int));
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
    int *args1 = malloc(sizeof(int));
    args1[0] = 4;
    int *args2 = malloc(sizeof(int));
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
    int *args1 = malloc(sizeof(int));
    args1[0] = 7;
    int *args2 = malloc(sizeof(int));
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
    int *args1 = malloc(sizeof(int));
    args1[0] = 7;
    int *args2 = malloc(sizeof(int));
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
    int *args1 = malloc(sizeof(int));
    args1[0] = 14;
    int *args2 = malloc(sizeof(int));
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

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

frame_t *create_test_frame_invoked() {
    int *args1 = malloc(sizeof(int));
    args1[0] = 7;

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction4 = constructor_instruction(1, I_RETURN, NULL);

    instruction_t **instructions = malloc(sizeof(instruction_t *) * 2);
    instructions[0] = instruction1;
    instructions[1] = instruction4;

    frame_t *frame = constructor_frame(0, INT_RETURN, instructions, 2);

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

int main() {
    printf("test_kernel_div_i(): \n");
    if (test_kernel_div_i() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }

    printf("test_kernel_add(): \n");
    if (test_kernel_add() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }

    printf("test_kernel_mul(): \n");
    if (test_kernel_mul() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }

    printf("test_kernel_compare_1(): \n");
    if (test_kernel_compare_1() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }

    printf("test_kernel_compare_2(): \n");
    if (test_kernel_compare_2() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }

    printf("test_kernel_invoke(): \n");
    if (test_kernel_invoke() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }
}