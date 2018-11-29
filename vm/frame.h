//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

#include "instruction.h"

struct frame {
    char *name;

    int pointer_stack;
    int *stack;

    int *local_pool;

    int instructions_size;
    instruction *instructions;
};

typedef struct frame frame;

void go(frame*);

#endif //VM_FRAME_H
