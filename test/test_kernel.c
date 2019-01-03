//
// Created by fin on 03.01.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "test_kernel.h"
#include "test.h"
#include "../frame.h"
#include "../stack_frame.h"

frame_t *create_test_frame() {
    int args1[1] = {1};
    int args2[1] = {2};

    instruction_t *instruction1 = constructor_instruction(0, CONST, args1);
    instruction_t *instruction2 = constructor_instruction(1, CONST, args2);
    instruction_t *instruction3 = constructor_instruction(2, ADD, NULL);
    instruction_t *instruction4 = constructor_instruction(3, RETURN, NULL);

    instruction_t *instructions = malloc(sizeof(instruction_t) * 4);
    instructions[0] = *instruction1;
    instructions[1] = *instruction2;
    instructions[2] = *instruction3;
    instructions[3] = *instruction4;

    frame_t *frame = constructor_frame(0, VOID_RETURN, instructions, 4);

    stack_frame_t *stack_frame = get_stack_frame();
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = frame;
    stack_frame->frames[stack_frame->number_frames++] = frame;

    return frame;
}

test_result_t test_kernel_def() {
    init_stack_frame();

    frame_t *frame = create_test_frame();
    execute_frame(frame);

    if(*frame->work_stack == 3){
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
    /*
    main()
    0: iconst_1
    1: iconst_2
    2: iadd
    3: return
     */
}

int main() {
    printf("read_file_test(): \n");
    if (test_kernel_def() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }
}