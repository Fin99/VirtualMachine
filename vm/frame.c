#include <stdio.h>
#include "frame.h"

void go(frame *frame) {
    for (int i = 0; i < frame->instructions_size; ++i) {
        execute(frame, &frame->instructions[i]);
    }
}