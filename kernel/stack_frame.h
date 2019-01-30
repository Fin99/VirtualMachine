//
// Created by fin on 03.01.19.
//

#ifndef VIRTUALMACHINE_STACKFRAME_H
#define VIRTUALMACHINE_STACKFRAME_H

#include "frame.h"
#include "class.h"

#define MAX_STACK_FRAME_SIZE 128
#define MAX_NUMBER_FRAMES 128
#define MAX_NUMBER_CLASSES 128


#define DEBUG 1
#define DEBUG_HEAP 0
#define DEBUG_INSTRUCTION 0
#define DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT 2

typedef struct stack_frame stack_frame_t;
struct stack_frame {
    frame_t **stack_frame;
    long long index_first_element_stack_frame;

    frame_t **frames;
    long long number_frames;

    class_t **classes;
    long long number_classes;
};

void init_stack_frame();

void destructor_stack_frame();

stack_frame_t *get_stack_frame();

frame_t *find_frame(long long index_frame);

class_t *find_class(long long index_class);

#endif //VIRTUALMACHINE_STACKFRAME_H
