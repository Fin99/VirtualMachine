#include <stdlib.h>
#include <stdio.h>
#include "frame.h"
#include "stack_frame.h"

#define DEBUG 1
#define DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT 5

instruction_t *constructor_instruction(int index, type_instruction_t type, int *args) {
    instruction_t *instruction = malloc(sizeof(instruction_t));

    instruction->index_instruction = index;
    instruction->type_instruction = type;
    instruction->args = args;

    return instruction;
}

void destructor_instruction(instruction_t *instruction) {
    free(instruction->args);
    free(instruction);
}

void print_name_instruction(instruction_t instruction) {
    switch (instruction.type_instruction) {
        case ADD:
            printf("add");
            break;
        case DIV_I:
            printf("div_i");
            break;
        case MUL:
            printf("mul");
            break;
        case COMPARE:
            printf("compare");
            break;
        case NEW:
            printf("new %s", find_class(instruction.args[0])->name);
            break;
        case LOAD:
            printf("load %i", instruction.args[0]);
            break;
        case CONST:
            printf("const %i", instruction.args[0]);
            break;
        case STORE:
            printf("store %i", instruction.args[0]);
            break;
        case INVOKE:
            printf("invoke %s", find_frame(instruction.args[0])->name);
            break;
        case RETURN:
            printf("return");
            break;
        case I_RETURN:
            printf("i_return");
            break;
    }
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

void mul(frame_t *frame, int **work_stack) {
    int first_element = (*work_stack)[frame->index_first_element_work_stack];
    int second_element = (*work_stack)[--frame->index_first_element_work_stack];

    (*work_stack)[frame->index_first_element_work_stack] = first_element * second_element;
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

void print_work_stack(frame_t *frame) {
    printf("Work stack(size = %i): ", frame->index_first_element_work_stack + 1);
    for (int i = frame->index_first_element_work_stack; i >= 0; --i) {
        printf("~%i~", frame->work_stack[i]);
    }
    printf("\n");
}

void print_local_pool(frame_t *frame) {
    printf("Local pool(first %i elements): ", DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT);
    for (int i = 0; i < DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT; ++i) {
        printf("|%i|", frame->local_pool[i]);
    }
    printf("\n");
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
        case DIV_I:
            div_i(frame, work_stack);
            break;
        case MUL:
            mul(frame, work_stack);
            break;
        case COMPARE:
            compare(work_stack, frame);
            break;
        case NEW:

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
        case I_RETURN:
            ireturn(stack_frame, work_stack);
            break;
    }

    if (DEBUG) {
        printf("Index frame: %i. Instruction: ", frame->index_frame);
        print_name_instruction(instruction);
        printf("\n");
        print_work_stack(frame);
        print_local_pool(frame);
    }
}