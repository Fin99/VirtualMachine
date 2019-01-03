#include "frame.h"
#include "stack_frame.h"

void add(frame_t *top_frame, int **work_stack) {

    int *first_element = work_stack[top_frame->index_first_element_work_stack];
    int *second_element = work_stack[top_frame->index_first_element_work_stack - 1];

    *second_element = *first_element + *second_element;

    top_frame->index_first_element_work_stack--;
}

void execute_instruction(instruction_t *instruction) {
    stack_frame_t *stack_frame = get_stack_frame();
    frame_t *top_frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    int **work_stack = top_frame->work_stack;

    switch (instruction->type_instruction) {
        case ADD:
            add(top_frame, work_stack);
            break;
        case LOAD:
            break;
        case CONST:
            break;
        case STORE:
            break;
        case INVOKE:
            break;
        case RETURN:
            break;
        case IRETURN:
            break;
    }
}