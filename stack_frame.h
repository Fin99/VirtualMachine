//
// Created by fin on 03.01.19.
//

#ifndef VIRTUALMACHINE_STACKFRAME_H
#define VIRTUALMACHINE_STACKFRAME_H

#include "frame.h"

#define MAX_STACK_FRAME_SIZE 128;

typedef struct stack_frame stack_frame_t;
struct stack_frame {
    frame_t *stack_frame;
    int index_first_element_stack_frame;
};

#endif //VIRTUALMACHINE_STACKFRAME_H
