#include <stdlib.h>
#include <stdio.h>
#include "frame.h"
#include "stack_frame.h"
#include "gc.h"


instruction_t *constructor_instruction(long long index, type_instruction_t type, long long *args) {
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
        case GET_FIELD:
            printf("get_field %lli", instruction.args[0]);
            break;
        case SET_FIELD:
            printf("set_field %lli", instruction.args[0]);
            break;
        case LOAD:
            printf("load %lli", instruction.args[0]);
            break;
        case CONST:
            printf("const %lli", instruction.args[0]);
            break;
        case STORE:
            printf("store %lli", instruction.args[0]);
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

void add(frame_t *frame, long long **work_stack) {

    long long first_element = (*work_stack)[frame->index_first_element_work_stack];
    long long second_element = (*work_stack)[--frame->index_first_element_work_stack];

    (*work_stack)[frame->index_first_element_work_stack] = first_element + second_element;
}

void div_i(frame_t *frame, long long **work_stack) {
    long long first_element = (*work_stack)[frame->index_first_element_work_stack];
    long long second_element = (*work_stack)[frame->index_first_element_work_stack - 1];

    (*work_stack)[frame->index_first_element_work_stack] = first_element / second_element;
    (*work_stack)[frame->index_first_element_work_stack - 1] = first_element % second_element;
}

void mul(frame_t *frame, long long **work_stack) {
    long long first_element = (*work_stack)[frame->index_first_element_work_stack];
    long long second_element = (*work_stack)[--frame->index_first_element_work_stack];

    (*work_stack)[frame->index_first_element_work_stack] = first_element * second_element;
}

void invoke(stack_frame_t *stack_frame, instruction_t instruction) {
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = find_frame(*instruction.args);
    execute_frame(stack_frame->stack_frame[stack_frame->index_first_element_stack_frame]);
}

void ireturn(stack_frame_t *stack_frame, long long **work_stack) {
    stack_frame->index_first_element_stack_frame--;

    long long value = **work_stack;
    frame_t *old_frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    old_frame->work_stack[++old_frame->index_first_element_work_stack] = value;
}

void compare(long long **work_stack, frame_t *frame) {
    (*work_stack)[frame->index_first_element_work_stack - 1] = (*work_stack)[frame->index_first_element_work_stack] -
                                                               (*work_stack)[frame->index_first_element_work_stack - 1];
    frame->index_first_element_work_stack--;
}

void get_field(long long **work_stack, frame_t *frame, long long number_field) {
    object_t *object = (object_t *) (*work_stack)[frame->index_first_element_work_stack];
    (*work_stack)[frame->index_first_element_work_stack] = object->fields[number_field];
}

void set_field(long long **work_stack, frame_t *frame, long long number_field) {
    object_t *object = (object_t *) (*work_stack)[frame->index_first_element_work_stack];
    long long value = (*work_stack)[frame->index_first_element_work_stack - 1];
    object->fields[number_field] = value;
    frame->index_first_element_work_stack -= 2;
}

void print_work_stack(frame_t *frame) {
    printf("Work stack(size = %lli): ", frame->index_first_element_work_stack + 1);
    for (long long i = frame->index_first_element_work_stack; i >= 0; --i) {
        printf("~%lli~", frame->work_stack[i]);
    }
    printf("\n");
}

void print_local_pool(frame_t *frame) {
    printf("Local pool(first %i elements): ", DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT);
    for (long long i = 0; i < DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT; ++i) {
        printf("|%lli|", frame->local_pool[i]);
    }
    printf("\n");
}

void execute_instruction(instruction_t instruction) {
    stack_frame_t *stack_frame = get_stack_frame();
    frame_t *frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    long long **local_pool = &frame->local_pool;
    long long **work_stack = &frame->work_stack;

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
            (*work_stack)[++frame->index_first_element_work_stack] = new_object(find_class(*instruction.args));
            break;
        case GET_FIELD:
            get_field(work_stack, frame, *instruction.args);
            break;
        case SET_FIELD:
            set_field(work_stack, frame, *instruction.args);
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
        printf("Frame: %s. Instruction: ", frame->name);
        print_name_instruction(instruction);
        printf("\n");
        print_work_stack(frame);
        print_local_pool(frame);
    }
}