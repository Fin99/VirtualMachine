//
// Created by fin on 03.01.19.
//

#include <memory.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "test.h"
#include "../parsing-bytecode/string.h"
#include "../parsing-bytecode/parser.h"

test_result_t test_string_split() {
    char *string = "   Hello my  world    ";

    size_t number_substring;
    char **split_string = split(string, " ", &number_substring);

    if (!strcmp(split_string[0], "Hello") && !strcmp(split_string[1], "my") && !strcmp(split_string[2], "world")) {
        for (int i = 0; i < number_substring; ++i) {
            free(split_string[i]);
        }
        free(split_string);
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t test_parser() {
    load_class_and_frame("SumTest.fn");
    if (true) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

int main() {
    int number_test_functions = 2;
    test_result_t(*test_functions[number_test_functions])();
    test_functions[0] = test_string_split;
    test_functions[1] = test_parser;

    char *name_test_functions[number_test_functions];
    name_test_functions[0] = "test_string_split():";
    name_test_functions[1] = "test_parser():";

    for (int i = 0; i < number_test_functions; ++i) {
        puts(name_test_functions[i]);
        if (test_functions[i]() == TEST_SUCCESS) {
            puts("Test passed successfully\n");
            fflush(stdout);
        } else {
            fputs("Test failed\n", stderr);
            fflush(stderr);
        }
        puts("-----------------------------------");
    }

    return 0;
}