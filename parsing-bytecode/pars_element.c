//
// Created by fin on 29.01.19.
//

#include <stdio.h>
#include <malloc.h>
#include "pars_element.h"
#include "string.h"


arg_t *pars_function_pre_args(char *text) {
    arg_t *args = malloc(sizeof(arg_t));

    args[0].name_arg = malloc(strlen("name") + 1);
    strcpy(args[0].name_arg, "name");

    args[0].value_arg = malloc(strlen(text) - strlen("function "));
    strcpy(args[0].value_arg, text + strlen("function "));

    return args;
}

arg_t *pars_function_args(char *text) {
    unsigned long number_args;
    char **split_args = split(text, "\n", &number_args);

    arg_t *args = malloc(sizeof(arg_t) * number_args);
    for (int i = 0; i < number_args; ++i) {
        unsigned long size;
        char **split_arg = split(split_args[i], "=", &size);

        args[i].name_arg = malloc(strlen(split_arg[0]) + 1);
        strcpy(args[i].name_arg, split_arg[0]);

        args[i].value_arg = malloc(strlen(split_arg[1]) + 1);
        strcpy(args[i].value_arg, split_arg[1]);

        destructor_split_string(split_arg, size);
    }

    destructor_split_string(split_args, number_args);

    return args;
}

arg_t *pars_class_pre_args(char *text) {
    arg_t *args = malloc(sizeof(arg_t));

    args[0].name_arg = malloc(strlen("name") + 1);
    strcpy(args[0].name_arg, "name");

    args[0].value_arg = malloc(strlen(text) - strlen("class "));
    strcpy(args[0].value_arg, text + strlen("class "));

    return args;
}

arg_t *pars_class_args(char *text) {
    unsigned long number_args;
    char **split_args = split(text, "\n", &number_args);

    arg_t *args = malloc(sizeof(arg_t) * number_args);
    for (int i = 0; i < number_args; ++i) {
        unsigned long size;
        char **split_arg = split(split_args[i], "=", &size);

        args[i].name_arg = malloc(strlen(split_arg[0]) + 1);
        strcpy(args[i].name_arg, split_arg[0]);

        args[i].value_arg = malloc(strlen(split_arg[1]) + 1);
        strcpy(args[i].value_arg, split_arg[1]);

        destructor_split_string(split_arg, size);
    }

    destructor_split_string(split_args, number_args);

    return args;
}

pars_element_t *pars_text(char *text) {
    unsigned long number_elements;
    char **split_text = split(text, "}", &number_elements);

    pars_element_t *pars_elements = malloc(sizeof(pars_element_t) * number_elements);

    for (int i = 0; i < number_elements; ++i) {
        if (split_text[i][0] == 'c' || split_text[i][1] == 'c') {
            pars_elements[i].type_parse_element = CLASS;

            unsigned long size;
            char **split_element = split(split_text[i], "{", &size);

            if (split_element[0][0] == '\n') {
                pars_elements[i].pre_args = pars_class_pre_args(split_element[0] + 1);
            } else {
                pars_elements[i].pre_args = pars_class_pre_args(split_element[0]);
            }
            pars_elements[i].args = pars_class_args(split_element[1]);

            destructor_split_string(split_element, size);
        } else if (split_text[i][0] == 'f' || split_text[i][1] == 'f') {
            pars_elements[i].type_parse_element = FUNCTION;

            unsigned long size;
            char **split_element = split(split_text[i], "{", &size);

            if (split_element[0][0] == '\n') {
                pars_elements[i].pre_args = pars_function_pre_args(split_element[0] + 1);
            } else {
                pars_elements[i].pre_args = pars_function_pre_args(split_element[0]);
            }
            pars_elements[i].args = pars_function_args(split_element[1]);

            destructor_split_string(split_element, size);
        }
    }

    destructor_split_string(split_text, number_elements);
    return pars_elements;
}