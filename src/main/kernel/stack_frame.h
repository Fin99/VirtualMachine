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
#define DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT 3

struct stack_frame {
    struct frame **stack_frame;
    int index_first_element_stack_frame;

    struct frame **frames;
    int number_frames;

    struct class **classes;
    int number_classes;
};

void init_stack_frame();

void destructor_stack_frame();

struct stack_frame *get_stack_frame();

struct frame *find_frame(char *frame_name);

struct class *find_class(char *class_name);

#endif //VIRTUALMACHINE_STACKFRAME_H
