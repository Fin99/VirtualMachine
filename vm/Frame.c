#include <stdio.h>
#include "Frame.h"

void go(Frame *frame) {
    for (int i = 0; i < frame->instructionsSize; ++i) {
        execute(frame, &frame->instructions[i]);
    }
}