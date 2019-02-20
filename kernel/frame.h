//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

#include <stdbool.h>
#include <stdint.h>
#include "instruction.h"

#define WORK_STACK_SIZE_MAX 128
#define LOCAL_POOL_SIZE_MAX 128

enum type_frame {
    VOID_RETURN,
    INT_RETURN,
    OBJECT_RETURN
};

struct frame {
    enum type_frame type_frame;

    int index_frame;
    char *name;

    int number_args;

    struct instruction **instructions;
    int number_instructions;

    int64_t *work_stack;
    int index_first_element_work_stack;
    bool *is_work_stack_element_object;

    int64_t *local_pool;
    bool *is_local_pool_element_object;
};

struct frame *constructor_frame(int index_frame, char *name, enum type_frame type_frame, struct instruction **instructions,
                           int number_instructions, int number_args);

void destructor_frame(struct frame *frame);

void execute_frame(struct frame *frame);

#endif //VM_FRAME_H
