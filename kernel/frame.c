#include <stdlib.h>
#include "frame.h"

frame_t *constructor_frame(long long index_frame, type_frame_t type_frame, instruction_t **instructions,
                           long long number_instructions) {
    frame_t *frame = malloc(sizeof(frame_t));
    frame->index_frame = index_frame;
    frame->type_frame = type_frame;

    frame->work_stack = malloc(sizeof(long long) * WORK_STACK_SIZE_MAX);
    frame->index_first_element_work_stack = -1;
    frame->is_work_stack_element_object = malloc(sizeof(bool) * WORK_STACK_SIZE_MAX);

    frame->local_pool = malloc(sizeof(long long) * LOCAL_POOL_SIZE_MAX);
    frame->is_local_pool_element_object = malloc(sizeof(bool) * LOCAL_POOL_SIZE_MAX);

    frame->instructions = instructions;
    frame->number_instructions = number_instructions;

    return frame;
}

void destructor_frame(frame_t *frame) {
    free(frame->work_stack);
    free(frame->is_work_stack_element_object);
    free(frame->local_pool);
    free(frame->is_local_pool_element_object);
    free(frame->name);

    for (long long i = 0; i < frame->number_instructions; ++i) {
        destructor_instruction(frame->instructions[i]);
    }
    free(frame->instructions);
    free(frame);
}

void execute_frame(frame_t *frame) {
    for (long long i = 0; i < frame->number_instructions; ++i) {
        execute_instruction(*frame->instructions[i]);
    }
}