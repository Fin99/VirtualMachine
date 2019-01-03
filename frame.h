//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

#include "instruction.h"

struct Frame {
    char *name;

    int pointerStack;
    int *stack;

    int locaPoolSize;
    int *localPool;

    int instructionsSize;
    instruction *instructions;
};

typedef struct Frame Frame;

void go(Frame*);

#endif //VM_FRAME_H
