#include <stdlib.h>
#include <stdio.h>
#include "frame.h"
#include "stack_frame.h"
#include "gc.h"


struct instruction *constructor_instruction(int index, enum type_instruction type, var *args) {
    struct instruction *instruction = malloc(sizeof(struct instruction));

    instruction->index_instruction = index;
    instruction->type_instruction = type;
    instruction->args = args;

    return instruction;
}

void destructor_instruction(struct instruction *instruction) {
    free(instruction->args);
    free(instruction);
}

void print_name_instruction(struct instruction instruction) {
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
            printf("new %s", (char *) instruction.args);
            break;
        case GET_FIELD:
            printf("get_field %li", instruction.args[0]);
            break;
        case SET_FIELD:
            printf("set_field %li", instruction.args[0]);
            break;
        case LOAD:
            printf("load %li", instruction.args[0]);
            break;
        case CONST:
            printf("const %li", instruction.args[0]);
            break;
        case STORE:
            printf("store %li", instruction.args[0]);
            break;
        case POP:
            printf("pop");
            break;
        case CLEAR_LOCAL_VARIABLE:
            printf("clear_local_variable %li", instruction.args[0]);
            break;
        case INVOKE:
            printf("invoke %s", (char *) instruction.args);
            break;
        case RETURN:
            printf("return");
            break;
        case I_RETURN:
            printf("i_return");
            break;
        case O_RETURN:
            printf("o_return");
            break;
        case IF_ACMPEQ:
            printf("if_acmpeq %li", instruction.args[0]);
            break;
        case IF_ACMPNE:
            printf("if_acmpne %li", instruction.args[0]);
            break;
        case GOTO:
            printf("goto %li", instruction.args[0]);
            break;
    }
}

void add(struct frame *frame, var **work_stack, bool **is_object) {

    var first_element = (*work_stack)[frame->index_first_element_work_stack];
    var second_element = (*work_stack)[--frame->index_first_element_work_stack];

    (*work_stack)[frame->index_first_element_work_stack] = first_element + second_element;
    (*is_object)[frame->index_first_element_work_stack] = false;
}

void div_i(struct frame *frame, var **work_stack, bool **is_object) {
    var first_element = (*work_stack)[frame->index_first_element_work_stack];
    var second_element = (*work_stack)[frame->index_first_element_work_stack - 1];

    (*work_stack)[frame->index_first_element_work_stack] = first_element / second_element;
    (*work_stack)[frame->index_first_element_work_stack - 1] = first_element % second_element;

    (*is_object)[frame->index_first_element_work_stack] = false;
    (*is_object)[frame->index_first_element_work_stack - 1] = false;
}

void mul(struct frame *frame, var **work_stack, bool **is_object) {
    var first_element = (*work_stack)[frame->index_first_element_work_stack];
    var second_element = (*work_stack)[--frame->index_first_element_work_stack];

    (*work_stack)[frame->index_first_element_work_stack] = first_element * second_element;
    (*is_object)[frame->index_first_element_work_stack] = false;
}

void compare(struct frame *frame, var **work_stack, bool **is_object) {
    (*work_stack)[frame->index_first_element_work_stack - 1] = (*work_stack)[frame->index_first_element_work_stack] -
                                                               (*work_stack)[frame->index_first_element_work_stack - 1];
    (*is_object)[frame->index_first_element_work_stack - 1] = false;
    frame->index_first_element_work_stack--;
}

void invoke(struct frame *frame, struct stack_frame *stack_frame, struct instruction instruction, var **work_stack,
            bool **is_object) {
    struct frame *new_frame = find_frame((char *) instruction.args);
    for (int i = 0; i < new_frame->number_args; ++i) {
        var element = (*work_stack)[frame->index_first_element_work_stack];
        new_frame->local_pool[i] = element;
        if ((*is_object)[frame->index_first_element_work_stack]) {
            new_frame->is_local_pool_element_object[i] = true;
        } else {
            new_frame->is_local_pool_element_object[i] = false;
        }
        frame->index_first_element_work_stack--;
    }
    stack_frame->stack_frame[++stack_frame->index_first_element_stack_frame] = new_frame;
    execute_frame(stack_frame->stack_frame[stack_frame->index_first_element_stack_frame]);
}

void get_field(var **work_stack, struct frame *frame, int number_field, bool **is_object) {
    struct object *object = (struct object *) (*work_stack)[frame->index_first_element_work_stack];
    (*work_stack)[frame->index_first_element_work_stack] = object->fields[number_field];
    (*is_object)[frame->index_first_element_work_stack] = object->is_field_object[number_field];
}

void set_field(var **work_stack, struct frame *frame, int number_field, bool **is_object) {
    struct object *object = (struct object *) (*work_stack)[frame->index_first_element_work_stack];
    var value = (*work_stack)[frame->index_first_element_work_stack - 1];
    object->fields[number_field] = value;
    object->is_field_object[number_field] = (*is_object)[frame->index_first_element_work_stack - 1];
    frame->index_first_element_work_stack -= 2;
}

void ireturn(struct stack_frame *stack_frame, var **work_stack) {
    stack_frame->index_first_element_stack_frame--;

    var value = **work_stack;
    struct frame *old_frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    old_frame->work_stack[++old_frame->index_first_element_work_stack] = value;
    old_frame->is_work_stack_element_object[old_frame->index_first_element_work_stack] = false;
}

void oreturn(struct stack_frame *stack_frame, var **work_stack) {
    stack_frame->index_first_element_stack_frame--;

    var value = **work_stack;
    struct frame *old_frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    old_frame->work_stack[++old_frame->index_first_element_work_stack] = value;
    old_frame->is_work_stack_element_object[old_frame->index_first_element_work_stack] = true;
}

void print_work_stack(struct frame *frame) {
    printf("Work stack(size = %i): ", frame->index_first_element_work_stack + 1);
    for (int i = frame->index_first_element_work_stack; i >= 0; --i) {
        if (frame->is_work_stack_element_object[i]) {
            printf("~%p(object)~", (void *) frame->work_stack[i]);
        } else {
            printf("~%li~", frame->work_stack[i]);
        }
    }
    printf("\n");
}

void print_local_pool(struct frame *frame) {
    printf("Local pool(first %i elements): ", DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT);
    for (int i = 0; i < DEBUG_NUMBER_ELEMENT_LOCAL_POOL_PRINT; ++i) {
        if (frame->is_local_pool_element_object[i]) {
            printf("|%p(object)|", (void *) frame->local_pool[i]);
        } else {
            printf("|%li|", frame->local_pool[i]);
        }
    }
    printf("\n");
}

void new(struct frame *frame, struct instruction instruction, var **work_stack, bool **is_work_stack_element_object) {
    var object = new_object(find_class((char *) instruction.args));
    (*work_stack)[++frame->index_first_element_work_stack] = object;
    (*is_work_stack_element_object)[frame->index_first_element_work_stack] = true;
}

bool if_acmpeq(struct frame *frame, var **work_stack) {
    var first_element = (*work_stack)[frame->index_first_element_work_stack];
    var second_element = (*work_stack)[frame->index_first_element_work_stack - 1];

    frame->index_first_element_work_stack -= 2;

    if (first_element - second_element == 0) {
        return true;
    } else {
        return false;
    }
}

int *execute_instruction(struct instruction instruction) {
    struct stack_frame *stack_frame = get_stack_frame();
    struct frame *frame = stack_frame->stack_frame[stack_frame->index_first_element_stack_frame];
    var **local_pool = &frame->local_pool;
    var **work_stack = &frame->work_stack;
    bool **is_work_stack_element_object = &frame->is_work_stack_element_object;
    bool **is_local_pool_element_object = &frame->is_local_pool_element_object;

    int *index_jump = NULL;

    switch (instruction.type_instruction) {
        case ADD:
            add(frame, work_stack, is_work_stack_element_object);
            break;
        case DIV_I:
            div_i(frame, work_stack, is_work_stack_element_object);
            break;
        case MUL:
            mul(frame, work_stack, is_work_stack_element_object);
            break;
        case COMPARE:
            compare(frame, work_stack, is_work_stack_element_object);
            break;
        case NEW:
            new(frame, instruction, work_stack, is_work_stack_element_object);
            break;
        case GET_FIELD:
            get_field(work_stack, frame, (int) *instruction.args, is_work_stack_element_object);
            break;
        case SET_FIELD:
            set_field(work_stack, frame, (int) *instruction.args, is_work_stack_element_object);
            break;
        case LOAD:
            (*work_stack)[++frame->index_first_element_work_stack] = (*local_pool)[*instruction.args];
            (*is_work_stack_element_object)[frame->index_first_element_work_stack] =
                    (*is_local_pool_element_object)[*instruction.args];
            break;
        case CONST:
            (*work_stack)[++frame->index_first_element_work_stack] = *instruction.args;
            (*is_work_stack_element_object)[frame->index_first_element_work_stack] = false;
            break;
        case STORE:
            (*local_pool)[*instruction.args] = (*work_stack)[frame->index_first_element_work_stack--];
            (*is_local_pool_element_object)[*instruction.args] =
                    (*is_work_stack_element_object)[frame->index_first_element_work_stack + 1];
            break;
        case POP:
            frame->index_first_element_work_stack--;
            break;
        case CLEAR_LOCAL_VARIABLE:
            (*local_pool)[*instruction.args] = 0;
            (*is_local_pool_element_object)[*instruction.args] = false;
            break;
        case INVOKE:
            invoke(frame, stack_frame, instruction, work_stack, is_work_stack_element_object);
            break;
        case RETURN:
            if (get_gc() != NULL && get_gc()->number_objects > 0)
                start_gc();
            stack_frame->index_first_element_stack_frame--;
            break;
        case I_RETURN:
            ireturn(stack_frame, work_stack);
            break;
        case O_RETURN:
            oreturn(stack_frame, work_stack);
            break;
        case IF_ACMPEQ:
            if (if_acmpeq(frame, work_stack)) {
                index_jump = malloc(8);
                *index_jump = (int) *instruction.args;
            }
            break;
        case IF_ACMPNE:
            if (!if_acmpeq(frame, work_stack)) {
                index_jump = malloc(8);
                *index_jump = (int) *instruction.args;
            }
            break;
        case GOTO:
            index_jump = malloc(8);
            *index_jump = (int) *instruction.args;
            break;
    }

    if (DEBUG || DEBUG_INSTRUCTION) {
        printf("Frame: %s. Instruction: ", frame->name);
        print_name_instruction(instruction);
        printf("\n");
        print_work_stack(frame);
        print_local_pool(frame);
        printf("\n");
    }

    return index_jump;
}