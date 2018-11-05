//
// Created by Fin on 04.11.2018.
//


#ifndef VM_FRAME_H

#define VM_FRAME_H

#include "Instruction.h"

typedef struct {
    char *name;
    int *stack;
    int *localPool;
    int pointerStack;
    Instruction *instructions;
} Frame;
#endif //VM_FRAME_H
