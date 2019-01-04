#include <stdlib.h>
#include "stack_frame.h"

static stack_frame_t *stack_frame = NULL;

void destructor_stack_frame() {
    free(stack_frame->stack_frame);

    for (int i = 0; i < stack_frame->number_frames; ++i) {
        destructor_frame(stack_frame->frames[i]);
    }
    free(stack_frame->frames);

    for (int i = 0; i < stack_frame->number_classes; ++i) {
        destructor_class(stack_frame->classes[i]);
    }
    free(stack_frame->classes);

    free(stack_frame);
}

void init_stack_frame() {
    if (stack_frame != NULL) {
        destructor_stack_frame(stack_frame);
    }
    stack_frame = malloc(sizeof(stack_frame_t));

    stack_frame->stack_frame = malloc(sizeof(frame_t) * MAX_STACK_FRAME_SIZE);
    stack_frame->index_first_element_stack_frame = -1;

    stack_frame->frames = malloc(sizeof(frame_t) * MAX_NUMBER_FRAMES);
    stack_frame->number_frames = 0;
}


stack_frame_t *get_stack_frame() {
    return stack_frame;
}

frame_t *find_frame(int index_frame) {
    for (int i = 0; i < stack_frame->number_frames; ++i) {
        if (stack_frame->frames[i]->index_frame == index_frame) {
            return stack_frame->frames[i];
        }
    }

    return NULL;
}

class_t *find_class(int index_class){
    for (int i = 0; i < stack_frame->number_frames; ++i) {
        if (stack_frame->classes[i]->index_class == index_class) {
            return stack_frame->classes[i];
        }
    }

    return NULL;
}