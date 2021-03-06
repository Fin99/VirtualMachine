//
// Created by fin on 29.01.19.
//

#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "../commons/file.h"
#include "pars_element.h"
#include "../../kernel/class.h"
#include "../../kernel/stack_frame.h"

void load_class(struct pars_element pars_element) {
    static int count_frames = 0;

    char *class_name = malloc(strlen(pars_element.pre_args[0].values_arg[0]) + 1);
    strcpy(class_name, pars_element.pre_args[0].values_arg[0]);

    struct class *class = constructor_class(count_frames++, class_name,
                                            (int) strtol(pars_element.args[0].values_arg[0], NULL, 10));

    get_stack_frame()->classes[get_stack_frame()->number_classes++] = class;
}

void load_frame(struct pars_element pars_element) {
    static int count_frames = 0;

    struct instruction **instructions = malloc(8 * pars_element.number_args);

    enum type_instruction type_instruction;
    for (int i = 0; i < pars_element.number_args; ++i) {
        if (!strcmp(pars_element.args[i].name_arg, "add")) {
            type_instruction = ADD;
        } else if (!strcmp(pars_element.args[i].name_arg, "div_i")) {
            type_instruction = DIV_I;
        } else if (!strcmp(pars_element.args[i].name_arg, "mul")) {
            type_instruction = MUL;
        } else if (!strcmp(pars_element.args[i].name_arg, "compare")) {
            type_instruction = COMPARE;
        } else if (!strcmp(pars_element.args[i].name_arg, "new")) {
            type_instruction = NEW;
        } else if (!strcmp(pars_element.args[i].name_arg, "get_field")) {
            type_instruction = GET_FIELD;
        } else if (!strcmp(pars_element.args[i].name_arg, "set_field")) {
            type_instruction = SET_FIELD;
        } else if (!strcmp(pars_element.args[i].name_arg, "load")) {
            type_instruction = LOAD;
        } else if (!strcmp(pars_element.args[i].name_arg, "const")) {
            type_instruction = CONST;
        } else if (!strcmp(pars_element.args[i].name_arg, "store")) {
            type_instruction = STORE;
        } else if (!strcmp(pars_element.args[i].name_arg, "pop")) {
            type_instruction = POP;
        } else if (!strcmp(pars_element.args[i].name_arg, "clear_local_variable")) {
            type_instruction = CLEAR_LOCAL_VARIABLE;
        } else if (!strcmp(pars_element.args[i].name_arg, "invoke")) {
            type_instruction = INVOKE;
        } else if (!strcmp(pars_element.args[i].name_arg, "return")) {
            type_instruction = RETURN;
        } else if (!strcmp(pars_element.args[i].name_arg, "i_return")) {
            type_instruction = I_RETURN;
        } else if (!strcmp(pars_element.args[i].name_arg, "o_return")) {
            type_instruction = O_RETURN;
        } else if (!strcmp(pars_element.args[i].name_arg, "if_acmpeq")) {
            type_instruction = IF_ACMPEQ;
        } else if (!strcmp(pars_element.args[i].name_arg, "if_acmpne")) {
            type_instruction = IF_ACMPNE;
        } else if (!strcmp(pars_element.args[i].name_arg, "goto")) {
            type_instruction = GOTO;
        } else {
            type_instruction = -1;
            //todo error
        }

        var *instruction_args = malloc(sizeof(var) * pars_element.args[i].number_values);
        for (int j = 0; j < pars_element.args[i].number_values; ++j) {
            char *end;
            var arg = strtoll(pars_element.args[i].values_arg[j], &end, 10);
            if (!strcmp(end, "")) {
                instruction_args[j] = arg;
            } else {
                free(instruction_args);
                instruction_args = malloc(strlen(end) + 1);
                strcpy((char *) instruction_args, end);
            }
        }

        instructions[i] = constructor_instruction(i, type_instruction, instruction_args);
    }


    enum type_frame type_frame;
    if (pars_element.pre_args[0].values_arg[0][0] == 'v') {
        type_frame = VOID_RETURN;
    } else if (pars_element.pre_args[0].values_arg[0][0] == 'o') {
        type_frame = OBJECT_RETURN;
    } else if (pars_element.pre_args[0].values_arg[0][0] == 'i') {
        type_frame = INT_RETURN;
    } else {
        type_frame = -1;
        //todo error
    }

    char *frame_name = malloc(strlen(pars_element.pre_args[1].values_arg[0]) + 1);
    strcpy(frame_name, pars_element.pre_args[1].values_arg[0]);

    int number_args = 0;
    if (pars_element.number_pre_args == 3) {
        number_args = (int) strtol(pars_element.pre_args[2].values_arg[0], NULL, 10);
    }

    struct frame *frame = constructor_frame(count_frames++, frame_name, type_frame, instructions,
                                       (int) pars_element.number_args, number_args);

    get_stack_frame()->frames[get_stack_frame()->number_frames++] = frame;
}

void load_class_and_frame_from_file(char *file_name) {
    char *text = read_file(file_name);
    load_class_and_frame(text);
}

void load_class_and_frame(char *text) {
    size_t number_elements;
    struct pars_element *pars_elements = pars_text(text, &number_elements);

    for (int i = 0; i < number_elements; ++i) {
        switch (pars_elements[i].type_parse_element) {
            case CLASS:
                load_class(pars_elements[i]);
                break;
            case FUNCTION:
                load_frame(pars_elements[i]);
                break;
        }
    }

    free(text);
    destructor_pars_element(pars_elements, number_elements);
}