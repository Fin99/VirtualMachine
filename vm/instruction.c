#include "instruction.h"
#include "frame.h"


void iconst(frame *frame, int arg) {
    frame->pointer_stack++;
    frame->stack[frame->pointer_stack] = arg;
}

void istore(frame *frame, int index_local_pool) {
    frame->local_pool[index_local_pool] = frame->stack[frame->pointer_stack];
    frame->pointer_stack--;
}

void iload(frame *frame, int index_local_pool) {
    frame->pointer_stack++;
    frame->stack[frame->pointer_stack] = frame->local_pool[index_local_pool];
}

void iadd(frame *frame) {
    frame->stack[frame->pointer_stack - 1] = frame->stack[frame->pointer_stack] + frame->stack[frame->pointer_stack - 1];
    frame->pointer_stack--;
}

void invokeVirtual(frame *parent_frame, frame *child_frame) {
    run(child_frame);
}

//int ireturn(frame *frame) {
//    int ret = frame->stack[frame->pointer_stack];
//    frame->pointer_stack--;
//    return ret;
//}

void execute(frame *frame, instruction *instruction) {
    switch (instruction->type) {
        case ICONST:
            iconst(frame, instruction->arg);
            break;
        case ISTORE:
            istore(frame, instruction->arg);
            break;
//        case ALOAD:
//            break;
        case ILOAD:
            iload(frame, instruction->arg);
            break;
        case INVOKEVIRTUAL:
            invokeVirtual(frame, instruction->frame_arg);
            break;
        case IADD:
            iadd(frame);
            break;
//        case RETURN:
//            break;
//        case IRETURN:
//            break;
    }
}