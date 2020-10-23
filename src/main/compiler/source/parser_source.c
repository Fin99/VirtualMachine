//
// Created by fin on 29.01.19.
//

#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdio.h>
#include "parser_source.h"
#include "../commons/file.h"
#include "../commons/string.h"

void parse_class(char *text, char **class_name, char **class_body);

void parse_method(char *class_body, char **method_name, char **method_body);

void parse_instruction(char *method_body, char ***instructions, int *instructions_length);

void compile_init_number(char *instruction, char **local_pool, int *local_pool_size,
                         char ***bytecode_result, int *bytecode_result_length);

void compile_sum(char *instruction, char **local_pool, const int *local_pool_size,
                 char ***bytecode_result, int *bytecode_result_length);

void compile_mul(char *instruction, char **local_pool, const int *local_pool_size,
                 char ***bytecode_result, int *bytecode_result_length);

void compile_div(char *instruction, char **local_pool, const int *local_pool_size,
                 char ***bytecode_result, int *bytecode_result_length);

void compile_return(char *instruction,
                    char ***bytecode_result, int *bytecode_result_length);

int find_variable(char *variable_name, char **local_pool, int local_pool_size);

int calc_digits_count(int number);

int MAX_LOCAL_POOL_SIZE = 128;

char *parse_source_to_bytecode(char *file_name) {
    char *text = read_file(file_name);

    char *class_name;
    char *class_body;
    parse_class(text, &class_name, &class_body);

    char *method_name;
    char *method_body;
    parse_method(class_body, &method_name, &method_body);

    char **instructions;
    int instructions_length;
    parse_instruction(method_body, &instructions, &instructions_length);

    char **local_pool = malloc(sizeof(char *) * MAX_LOCAL_POOL_SIZE);
    int local_pool_size = 0;
    char **bytecode_result = malloc(1);
    int bytecode_result_length = 0;
    for (int i = 0; i < instructions_length; ++i) {
        compile_init_number(instructions[i], local_pool, &local_pool_size, &bytecode_result, &bytecode_result_length);
        compile_mul(instructions[i], local_pool, &local_pool_size, &bytecode_result, &bytecode_result_length);
        compile_div(instructions[i], local_pool, &local_pool_size, &bytecode_result, &bytecode_result_length);
        compile_sum(instructions[i], local_pool, &local_pool_size, &bytecode_result, &bytecode_result_length);
        compile_return(instructions[i], &bytecode_result, &bytecode_result_length);
    }

    puts("Result:");
    char *result = malloc(strlen("function void (){\n") + strlen(method_name) + 1);
    sprintf(result, "function void %s(){\n", method_name);

    size_t result_size = strlen(result);
    for (int i = 0; i < bytecode_result_length; ++i) {
        result = realloc(result, result_size + strlen(bytecode_result[i]) + 2);
        strcpy(result + result_size, bytecode_result[i]);
        strcpy(result + result_size + strlen(bytecode_result[i]), "\n");
        result_size = strlen(result);
    }

    size_t old_length = strlen(result);
    result = realloc(result, old_length + strlen("}\n") + 1);
    strcpy(result + old_length, "}");
//    puts(result);

    //free
    for (int i = 0; i < bytecode_result_length; ++i) {
        free(bytecode_result[i]);
    }
    free(bytecode_result);

    for (int i = 0; i < local_pool_size; ++i) {
        free(local_pool[i]);
    }
    free(local_pool);

    free(class_name);
    free(class_body);

    free(method_name);
    free(method_body);

    for (int i = 0; i < instructions_length; ++i) {
        free(instructions[i]);
    }
    free(instructions);

    free(text);

    return result;
}

void parse_class(char *text, char **class_name, char **class_body) {
    regex_t *regex_class = malloc(sizeof(regex_t));
    regcomp(regex_class, "class ([A-Za-z]*) \\{\n(.*?)}", REG_EXTENDED);
    regmatch_t classMatches[3];

    regexec(regex_class, text, 3, classMatches, 0);

    *class_name = malloc(sizeof(char) * (classMatches[1].rm_eo - classMatches[1].rm_so + 1));
    memcpy(*class_name, text + classMatches[1].rm_so, classMatches[1].rm_eo - classMatches[1].rm_so);
    (*class_name)[classMatches[1].rm_eo - classMatches[1].rm_so] = '\0';

    *class_body = malloc(sizeof(char) * (classMatches[2].rm_eo - classMatches[2].rm_so + 1));
    memcpy(*class_body, text + classMatches[2].rm_so, classMatches[2].rm_eo - classMatches[2].rm_so);
    (*class_body)[classMatches[2].rm_eo - classMatches[2].rm_so] = '\0';

    regfree(regex_class);
    free(regex_class);
}

void parse_method(char *class_body, char **method_name, char **method_body) {
    regex_t *regex_method = malloc(sizeof(regex_t));
    regcomp(regex_method, "void ([A-Za-z]*)\\() \\{\n(.*?)}", REG_EXTENDED);
    regmatch_t method_matches[3];

    regexec(regex_method, class_body, 3, method_matches, 0);

    *method_name = malloc(sizeof(char) * (method_matches[1].rm_eo - method_matches[1].rm_so + 1));
    memcpy(*method_name, class_body + method_matches[1].rm_so, method_matches[1].rm_eo - method_matches[1].rm_so);
    (*method_name)[method_matches[1].rm_eo - method_matches[1].rm_so] = '\0';

    *method_body = malloc(sizeof(char) * (method_matches[2].rm_eo - method_matches[2].rm_so + 1));
    memcpy(*method_body, class_body + method_matches[2].rm_so, method_matches[2].rm_eo - method_matches[2].rm_so);
    (*method_body)[method_matches[2].rm_eo - method_matches[2].rm_so] = '\0';

    regfree(regex_method);
    free(regex_method);
}

void parse_instruction(char *method_body, char ***instructions, int *instructions_length) {
    regex_t *regex_instruction = malloc(sizeof(regex_t));
    regcomp(regex_instruction, "([^;]*;)", REG_EXTENDED);

    regmatch_t instruction_matches[2];

    *instructions_length = 0;


    int first = 1;
    int shift = 0;
    while (1) {
        regexec(regex_instruction, method_body + shift, 2, instruction_matches, 0);

        if (instruction_matches[1].rm_eo > strlen(method_body + shift)) {
            break;
        }

        char instruction[instruction_matches[1].rm_eo - instruction_matches[1].rm_so + 1];
        memcpy(instruction, method_body + shift + instruction_matches[1].rm_so,
               instruction_matches[1].rm_eo - instruction_matches[1].rm_so);
        instruction[instruction_matches[1].rm_eo - instruction_matches[1].rm_so] = '\0';
        shift += instruction_matches[1].rm_eo;
        char *old_instruction = instruction;
        size_t trim_string_length = trim(instruction, strlen(instruction), old_instruction);
        if (trim_string_length == 0) {
            break;
        }

        if (!first) {
            char **old_instructions = *instructions;
            *instructions_length += 1;
            *instructions = malloc(sizeof(char *) * (*instructions_length));
            (*instructions)[(*instructions_length) - 1] = malloc(sizeof(char) * (strlen(instruction) + 1));

            for (int i = 0; i < (*instructions_length) - 1; ++i) {
                (*instructions)[i] = old_instructions[i];
            }
            free(old_instructions);
        } else {
            *instructions = malloc(sizeof(char *));
            (*instructions)[0] = malloc(sizeof(char) * (strlen(instruction) + 1));
            first = 0;
            *instructions_length = 1;
        }

        strcpy((*instructions)[(*instructions_length) - 1], instruction);
    }

    regfree(regex_instruction);
    free(regex_instruction);
}


void compile_init_number(char *instruction, char **local_pool, int *local_pool_size,
                         char ***bytecode_result, int *bytecode_result_length) {
    regex_t *regex_init_number = malloc(sizeof(regex_t));
    regcomp(regex_init_number, "number *([a-zA-Z_0-9]*) *= *([0-9]*) *;", REG_EXTENDED);
    regmatch_t init_number_matches[3];

    int matches = regexec(regex_init_number, instruction, 3, init_number_matches, 0);

    if (!matches && init_number_matches[2].rm_eo - init_number_matches[2].rm_so != 0) {
        char *number_name = malloc(sizeof(char) *
                                   (init_number_matches[1].rm_eo - init_number_matches[1].rm_so + 1));
        memcpy(number_name, instruction + init_number_matches[1].rm_so,
               init_number_matches[1].rm_eo - init_number_matches[1].rm_so);
        number_name[init_number_matches[1].rm_eo - init_number_matches[1].rm_so] = '\0';

        char *number_value = malloc(sizeof(char) *
                                    (init_number_matches[2].rm_eo - init_number_matches[2].rm_so + 1));
        memcpy(number_value, instruction + init_number_matches[2].rm_so,
               init_number_matches[2].rm_eo - init_number_matches[2].rm_so);
        number_value[init_number_matches[2].rm_eo - init_number_matches[2].rm_so] = '\0';

        local_pool[(*local_pool_size)++] = malloc(strlen(number_name) + 1);
        strcpy(local_pool[(*local_pool_size) - 1], number_name);

        *bytecode_result = realloc(*bytecode_result, sizeof(char *) * (2 + (*bytecode_result_length)));
        (*bytecode_result)[(*bytecode_result_length)] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":const ") + strlen(number_value) + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:const %s", *bytecode_result_length, number_value);
        (*bytecode_result_length)++;

        int index = (*local_pool_size) - 1;
        int digits_count = calc_digits_count(index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":store ") + digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:store %i", *bytecode_result_length,
                (*local_pool_size) - 1);
        (*bytecode_result_length)++;

        free(number_name);
        free(number_value);
    }

    regfree(regex_init_number);
    free(regex_init_number);
}

void compile_sum(char *instruction, char **local_pool, const int *local_pool_size,
                 char ***bytecode_result, int *bytecode_result_length) {
    regex_t *regex_sum = malloc(sizeof(regex_t));
    regcomp(regex_sum, "([a-zA-Z_0-9]*) *\\+ *([a-zA-Z_0-9]*)", REG_EXTENDED);
    regmatch_t sum_matches[3];

    int matches = regexec(regex_sum, instruction, 3, sum_matches, 0);

    if (!matches && sum_matches[2].rm_eo - sum_matches[2].rm_so != 0) {
        char *first_variable = malloc(sizeof(char) *
                                      (sum_matches[1].rm_eo - sum_matches[1].rm_so + 1));
        memcpy(first_variable, instruction + sum_matches[1].rm_so,
               sum_matches[1].rm_eo - sum_matches[1].rm_so);
        first_variable[sum_matches[1].rm_eo - sum_matches[1].rm_so] = '\0';

        char *second_variable = malloc(sizeof(char) *
                                       (sum_matches[2].rm_eo - sum_matches[2].rm_so + 1));
        memcpy(second_variable, instruction + sum_matches[2].rm_so,
               sum_matches[2].rm_eo - sum_matches[2].rm_so);
        second_variable[sum_matches[2].rm_eo - sum_matches[2].rm_so] = '\0';

        int first_variable_index = find_variable(first_variable, local_pool, *local_pool_size);
        int second_variable_index = find_variable(second_variable, local_pool, *local_pool_size);

        *bytecode_result = realloc(*bytecode_result, sizeof(char *) * (3 + (*bytecode_result_length)));

        int first_variable_digits_count = calc_digits_count(first_variable_index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":load ") + first_variable_digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:load %i", *bytecode_result_length,
                first_variable_index);
        (*bytecode_result_length)++;

        int second_variable_digits_count = calc_digits_count(second_variable_index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":load ") + second_variable_digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:load %i", *bytecode_result_length,
                second_variable_index);
        (*bytecode_result_length)++;

        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":add") + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:add", *bytecode_result_length);
        (*bytecode_result_length)++;

        free(first_variable);
        free(second_variable);
    }

    regfree(regex_sum);
    free(regex_sum);
}

void compile_mul(char *instruction, char **local_pool, const int *local_pool_size,
                 char ***bytecode_result, int *bytecode_result_length) {
    regex_t *regex_mul = malloc(sizeof(regex_t));
    regcomp(regex_mul, "([a-zA-Z_0-9]*) *\\* *([a-zA-Z_0-9]*)", REG_EXTENDED);
    regmatch_t mul_matches[3];

    int matches = regexec(regex_mul, instruction, 3, mul_matches, 0);

    if (!matches && mul_matches[2].rm_eo - mul_matches[2].rm_so != 0) {
        char *first_variable = malloc(sizeof(char) *
                                      (mul_matches[1].rm_eo - mul_matches[1].rm_so + 1));
        memcpy(first_variable, instruction + mul_matches[1].rm_so,
               mul_matches[1].rm_eo - mul_matches[1].rm_so);
        first_variable[mul_matches[1].rm_eo - mul_matches[1].rm_so] = '\0';

        char *second_variable = malloc(sizeof(char) *
                                       (mul_matches[2].rm_eo - mul_matches[2].rm_so + 1));
        memcpy(second_variable, instruction + mul_matches[2].rm_so,
               mul_matches[2].rm_eo - mul_matches[2].rm_so);
        second_variable[mul_matches[2].rm_eo - mul_matches[2].rm_so] = '\0';

        int first_variable_index = find_variable(first_variable, local_pool, *local_pool_size);
        int second_variable_index = find_variable(second_variable, local_pool, *local_pool_size);

        *bytecode_result = realloc(*bytecode_result, sizeof(char *) * (3 + (*bytecode_result_length)));

        int first_variable_digits_count = calc_digits_count(first_variable_index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":load ") + first_variable_digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:load %i", *bytecode_result_length,
                first_variable_index);
        (*bytecode_result_length)++;

        int second_variable_digits_count = calc_digits_count(second_variable_index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":load ") + second_variable_digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:load %i", *bytecode_result_length,
                second_variable_index);
        (*bytecode_result_length)++;

        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":mul") + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:mul", *bytecode_result_length);
        (*bytecode_result_length)++;

        free(first_variable);
        free(second_variable);
    }

    regfree(regex_mul);
    free(regex_mul);
}

void compile_div(char *instruction, char **local_pool, const int *local_pool_size,
                 char ***bytecode_result, int *bytecode_result_length) {
    regex_t *regex_div = malloc(sizeof(regex_t));
    regcomp(regex_div, "([a-zA-Z_0-9]*) */ *([a-zA-Z_0-9]*)", REG_EXTENDED);
    regmatch_t div_matches[3];

    int matches = regexec(regex_div, instruction, 3, div_matches, 0);

    if (!matches && div_matches[2].rm_eo - div_matches[2].rm_so != 0) {
        char *first_variable = malloc(sizeof(char) *
                                      (div_matches[1].rm_eo - div_matches[1].rm_so + 1));
        memcpy(first_variable, instruction + div_matches[1].rm_so,
               div_matches[1].rm_eo - div_matches[1].rm_so);
        first_variable[div_matches[1].rm_eo - div_matches[1].rm_so] = '\0';

        char *second_variable = malloc(sizeof(char) *
                                       (div_matches[2].rm_eo - div_matches[2].rm_so + 1));
        memcpy(second_variable, instruction + div_matches[2].rm_so,
               div_matches[2].rm_eo - div_matches[2].rm_so);
        second_variable[div_matches[2].rm_eo - div_matches[2].rm_so] = '\0';

        int first_variable_index = find_variable(first_variable, local_pool, *local_pool_size);
        int second_variable_index = find_variable(second_variable, local_pool, *local_pool_size);

        *bytecode_result = realloc(*bytecode_result, sizeof(char *) * (3 + (*bytecode_result_length)));

        int second_variable_digits_count = calc_digits_count(second_variable_index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":load ") + second_variable_digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:load %i", *bytecode_result_length,
                second_variable_index);
        (*bytecode_result_length)++;

        int first_variable_digits_count = calc_digits_count(first_variable_index);
        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":load ") + first_variable_digits_count + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:load %i", *bytecode_result_length,
                first_variable_index);
        (*bytecode_result_length)++;

        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":div_i") + 1));
        sprintf((*bytecode_result)[*bytecode_result_length], "%i:div_i", *bytecode_result_length);
        (*bytecode_result_length)++;

        free(first_variable);
        free(second_variable);
    }

    regfree(regex_div);
    free(regex_div);
}

void compile_return(char *instruction,
                    char ***bytecode_result, int *bytecode_result_length) {
    regex_t *regex_return = malloc(sizeof(regex_t));
    regcomp(regex_return, "return *;", REG_EXTENDED);
    regmatch_t return_matches[1];


    int matches = regexec(regex_return, instruction, 1, return_matches, 0);

    if (!matches) {
        *bytecode_result = realloc(*bytecode_result, sizeof(char *) * (1 + (*bytecode_result_length)));

        (*bytecode_result)[*bytecode_result_length] =
                malloc(sizeof(char) * (calc_digits_count(*bytecode_result_length)
                                       + strlen(":return") + 1));

        sprintf((*bytecode_result)[*bytecode_result_length], "%i:return", *bytecode_result_length);
        *bytecode_result_length += 1;
    }

    regfree(regex_return);
    free(regex_return);
}

int find_variable(char *variable_name, char **local_pool, int local_pool_size) {
    for (int i = 0; i < local_pool_size; ++i) {
        if (strcmp(local_pool[i], variable_name) == 0) {
            return i;
        }
    }
    printf("Variable %s not found", variable_name);
    exit(1);
}

int calc_digits_count(int number) {
    int count = 0;
    do {
        count++;
        number /= 10;
    } while (number != 0);

    return count;
}
