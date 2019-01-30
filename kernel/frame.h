//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

#include <stdbool.h>
#include "instruction.h"

#define WORK_STACK_SIZE_MAX 128
#define LOCAL_POOL_SIZE_MAX 128

typedef enum type_frame type_frame_t;
enum type_frame {
    VOID_RETURN,
    INT_RETURN,
    OBJECT_RETURN
};

typedef struct frame frame_t;
struct frame {
    long long index_frame;
    char *name;

    type_frame_t type_frame;

    instruction_t **instructions;
    long long number_instructions;

    long long *work_stack;
    long long index_first_element_work_stack;
    bool *is_work_stack_element_object;

    long long *local_pool;
    bool *is_local_pool_element_object;
};

frame_t *constructor_frame(long long index_frame, char *name, type_frame_t type_frame, instruction_t **instructions,
                           long long number_instructions);

void destructor_frame(frame_t *frame);

void execute_frame(frame_t *frame);

#endif //VM_FRAME_H
