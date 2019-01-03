//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

#include "instruction.h"

#define WORK_STACK_SIZE_MAX 128;
#define LOCAL_POOL_SIZE_MAX 128;

typedef enum type_frame type_frame_t;
enum type_frame {
    VOID_RETURN,
    INT_RETURN
};

typedef struct frame frame_t;
struct frame {
    int index_frame;

    type_frame_t type_frame;

    instruction_t *instructions;
    int number_instructions;

    int *work_stack;
    int index_last_element_work_stack;

    int *local_pool;
    int index_last_element_local_pool;
};

#endif //VM_FRAME_H
