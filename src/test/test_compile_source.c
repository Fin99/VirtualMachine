//
// Created by fin on 30.01.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "../main/compiler/source/parser_source.h"

enum test_result test_project_add() {
    parse_source_to_bytecode("src/test/source/test_project_add.fn");
    return TEST_SUCCESS;
}

int main() {
    int number_test_functions = 1;
    enum test_result(*test_functions[number_test_functions])();
    test_functions[0] = test_project_add;

    char *name_test_functions[number_test_functions];
    name_test_functions[0] = "test_project_add():";

    for (int i = 0; i < number_test_functions; ++i) {
        puts(name_test_functions[i]);
        if (test_functions[i]() == TEST_SUCCESS) {
            puts("Test passed successfully\n");
            fflush(stdout);
        } else {
            fputs("Test failed\n", stderr);
            fflush(stderr);
            exit(0);
        }
        puts("-----------------------------------");
    }

    return 0;
}