//
// Created by fin on 29.01.19.
//

#include <stdio.h>
#include <malloc.h>
#include "pars_element.h"
#include "string.h"

void destructor_pars_element(pars_element_t *pars_element, size_t number_elements) {
    for (int j = 0; j < number_elements; ++j) {
        for (int i = 0; i < pars_element[j].number_pre_args; ++i) {
            free(pars_element[j].pre_args[i].name_arg);
            for (int k = 0; k < pars_element[j].pre_args[i].number_values; ++k) {
                free(pars_element[j].pre_args[i].values_arg[k]);
            }
            if (pars_element[j].pre_args[i].number_values != 0) {
                free(pars_element[j].pre_args[i].values_arg);
            }
        }
        free(pars_element[j].pre_args);

        for (int i = 0; i < pars_element[j].number_args; ++i) {
            free(pars_element[j].args[i].name_arg);
            for (int k = 0; k < pars_element[j].args[i].number_values; ++k) {
                free(pars_element[j].args[i].values_arg[k]);
            }
            if (pars_element[j].args[i].number_values != 0) {
                free(pars_element[j].args[i].values_arg);
            }
        }
        free(pars_element[j].args);
    }


    free(pars_element);
}

void set_values_arg(arg_t *arg, size_t number_values, char **values) {
    arg->number_values = number_values;
    arg->values_arg = malloc(8 * number_values);
    for (int j = 0; j < number_values; ++j) {
        arg->values_arg[j] = malloc(strlen(values[j]) + 1);
        strcpy(arg->values_arg[j], values[j]);
    }
}

arg_t *pars_function_pre_args(char *text, size_t *number_args) {
    char **split_string = split(text, " ", number_args);

    arg_t *args = malloc(sizeof(arg_t) * (*number_args));

    args[0].name_arg = malloc(strlen("type_frame") + 1);
    strcpy(args[0].name_arg, "type_frame");

    set_values_arg(&args[0], 1, &split_string[0]);

    args[1].name_arg = malloc(strlen("name") + 1);
    strcpy(args[1].name_arg, "name");

    set_values_arg(&args[1], 1, &split_string[1]);

    destructor_split_string(split_string, *number_args);

    return args;
}

arg_t *pars_function_args(char *text, size_t *number_args) {
    char **split_args = split(text, "\n", number_args);

    arg_t *args = malloc(sizeof(arg_t) * (*number_args));
    for (int i = 0; i < *number_args; ++i) {
        unsigned long remove_number_args_size;
        char **remove_number_args = split(split_args[i], ":", &remove_number_args_size);
        unsigned long size;
        char **split_arg = split(remove_number_args[1], " ", &size);

        args[i].name_arg = malloc(strlen(split_arg[0]) + 1);
        strcpy(args[i].name_arg, split_arg[0]);

        if (size != 1) {
            set_values_arg(&args[i], size - 1, &split_arg[1]);
        } else {
            args[i].number_values = 0;
        }

        destructor_split_string(split_arg, size);
        destructor_split_string(remove_number_args, remove_number_args_size);
    }

    destructor_split_string(split_args, *number_args);

    return args;
}

arg_t *pars_class_pre_args(char *text, size_t *number_args) {
    *number_args = 1;
    arg_t *args = malloc(sizeof(arg_t));

    args[0].name_arg = malloc(strlen("name") + 1);
    strcpy(args[0].name_arg, "name");

    set_values_arg(&args[0], 1, &text);

    return args;
}

arg_t *pars_class_args(char *text, size_t *number_args) {
    char **split_args = split(text, "\n", number_args);

    arg_t *args = malloc(sizeof(arg_t) * (*number_args));
    for (int i = 0; i < *number_args; ++i) {
        unsigned long size;
        char **split_arg = split(split_args[i], "=", &size);

        args[i].name_arg = malloc(strlen(split_arg[0]) + 1);
        strcpy(args[i].name_arg, split_arg[0]);

        set_values_arg(&args[i], 1, &split_arg[1]);

        destructor_split_string(split_arg, size);
    }

    destructor_split_string(split_args, *number_args);

    return args;
}

pars_element_t *pars_text(char *text, size_t *number_elements) {
    char **split_text = split(text, "}", number_elements);

    pars_element_t *pars_elements = malloc(sizeof(pars_element_t) * (*number_elements));

    for (int i = 0; i < *number_elements; ++i) {
        size_t number_pre_args = 0;
        size_t number_args = 0;

        if (split_text[i][0] == 'c' || split_text[i][1] == 'c') {
            pars_elements[i].type_parse_element = CLASS;

            size_t size;
            char **split_element = split(split_text[i], "{", &size);

            if (split_element[0][0] == '\n') {
                pars_elements[i].pre_args = pars_class_pre_args(split_element[0] + 1 + strlen("class "),
                                                                &number_pre_args);
            } else {
                pars_elements[i].pre_args = pars_class_pre_args(split_element[0] + strlen("class "), &number_pre_args);
            }

            pars_elements[i].args = pars_class_args(split_element[1], &number_args);

            destructor_split_string(split_element, size);
        } else if (split_text[i][0] == 'f' || split_text[i][1] == 'f') {
            pars_elements[i].type_parse_element = FUNCTION;

            size_t size;
            char **split_element = split(split_text[i], "{", &size);

            if (split_element[0][0] == '\n') {
                pars_elements[i].pre_args = pars_function_pre_args(split_element[0] + 1 + strlen("function "),
                                                                   &number_pre_args);
            } else {
                pars_elements[i].pre_args = pars_function_pre_args(split_element[0] + strlen("function "),
                                                                   &number_pre_args);
            }
            pars_elements[i].args = pars_function_args(split_element[1], &number_args);

            destructor_split_string(split_element, size);
        }

        pars_elements[i].number_pre_args = number_pre_args;
        pars_elements[i].number_args = number_args;
    }

    destructor_split_string(split_text, *number_elements);
    return pars_elements;
}