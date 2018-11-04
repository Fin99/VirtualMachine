//
// Created by Fin on 04.11.2018.
//

#include "Instruction.h"

#ifndef VM_FRAME_H
#define VM_FRAME_H

#endif //VM_FRAME_H
typedef struct {
    int *stack;
    int *localPool;
    int pointerStack;
    Instruction instructions[];
} Frame;