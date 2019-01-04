#include <stdlib.h>
#include "frame.h"
#include "stack_frame.h"

instruction_t *constructor_instruction(int index, type_instruction_t type, int *args) {
    instruction_t *instruction = malloc(sizeof(instruction_t));

    instruction->index_instruction = index;
    instruction->type_instruction = type;
    instruction->args = args;

    return instruction;
}

void add(frame_t *frame, int **work_stack) {

    int first_element = (*work_stack)[frame->index_first_element_work_stack];
    int second_element = (*work_stack)[--frame->index_first_element_work_stack];

    (*work_stack)[frame->index_first_element_work_stack] = first_element + second_element;
}

void div_i(frame_t *frame, int **work_stack) {
    int first_element = (*work_stack)[frame->index_first_element_work_stack];
    int second_element = (*work_stack)[frame->index_first_element_work_stack - 1];

    (*work_stack)[frame->index_first_element_work_stack] = first_element / second_element;
    (*work_stack)[frame->index_first_element_work_stack - 1] = first_element % second_element;
}

void invoke(stack_frame_t *stack_frame, instruction_t instruction) {
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = find_frame(*instruction.args);
    execute_frame(stack_frame->stack_frame[stack_frame->index_first_element_stack_frame]);
}

void ireturn(stack_frame_t *stack_frame, int **work_stack) {
    stack_frame->index_first_element_stack_frame--;

    int value = **work_stack;
    frame_t *old_frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    old_frame->work_stack[++old_frame->index_first_element_work_stack] = value;
}

void compare(int **work_stack, frame_t *frame) {
    (*work_stack)[frame->index_first_element_work_stack - 1] = (*work_stack)[frame->index_first_element_work_stack] -
                                                               (*work_stack)[frame->index_first_element_work_stack - 1];
    frame->index_first_element_work_stack--;
}

void execute_instruction(instruction_t instruction) {
    stack_frame_t *stack_frame = get_stack_frame();
    frame_t *frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    int **local_pool = &frame->local_pool;
    int **work_stack = &frame->work_stack;

    switch (instruction.type_instruction) {
        case ADD:
            add(frame, work_stack);
            break;
        case DIV:
            div_i(frame, work_stack);
            break;
        case COMPARE:
            compare(work_stack, frame);
            break;
        case LOAD:
            (*work_stack)[++frame->index_first_element_work_stack] = (*local_pool)[*instruction.args];
            break;
        case CONST:
            (*work_stack)[++frame->index_first_element_work_stack] = *instruction.args;
            break;
        case STORE:
            (*local_pool)[*instruction.args] = (*work_stack)[frame->index_first_element_work_stack--];
            break;
        case INVOKE:
            invoke(stack_frame, instruction);
            break;
        case RETURN:
            stack_frame->index_first_element_stack_frame--;
            break;
        case IRETURN:
            ireturn(stack_frame, work_stack);
            break;
    }
}