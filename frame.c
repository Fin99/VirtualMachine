#include <stdlib.h>
#include "frame.h"

frame_t *constructor_frame(int index_frame, type_frame_t type_frame, instruction_t **instructions,
                           int number_instructions) {
    frame_t *frame = malloc(sizeof(frame_t));
    frame->index_frame = index_frame;
    frame->type_frame = type_frame;

    frame->work_stack = malloc(sizeof(int) * WORK_STACK_SIZE_MAX);
    frame->index_first_element_work_stack = -1;

    frame->local_pool = malloc(sizeof(int) * LOCAL_POOL_SIZE_MAX);

    frame->instructions = instructions;
    frame->number_instructions = number_instructions;

    return frame;
}

void destructor_frame(frame_t *frame){
    free(frame->work_stack);
    free(frame->local_pool);
    for (int i = 0; i < frame->number_instructions; ++i) {
        free(frame->instructions[i]);
    }
    free(frame->instructions);
    free(frame);
}

void execute_frame(frame_t *frame){
    for (int i = 0; i < frame->number_instructions; ++i) {
        execute_instruction(*frame->instructions[i]);
    }
}