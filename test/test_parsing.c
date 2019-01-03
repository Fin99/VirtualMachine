//
// Created by fin on 03.01.19.
//

#include <memory.h>
#include <stdio.h>
#include "test_parsing.h"
#include "test.h"
#include "../parsing-bytecode/file.h"
#include "../parsing-bytecode/string.h"

char *create_test_file(char *str) {
    char *file_name = "read_file_test";

    FILE *file = fopen(file_name, "w+b");

    fwrite(str, strlen(str), 1, file);

    fclose(file);
    return file_name;
}

test_result_t read_file_test() {
    char *str_test = "test\nme";
    char *file_name = create_test_file(str_test);

    const char *str_result = read_file(file_name);

    remove(file_name);

    if (!strcmp(str_test, str_result)) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

test_result_t string_split_test() {
    char *string = "   Hello my  world    ";

    size_t number_substring;
    char **split_string = split(string, " ", &number_substring);

    if (!strcmp(split_string[0], "Hello") && !strcmp(split_string[1], "my") && !strcmp(split_string[2], "world")) {
        return TEST_SUCCESS;
    } else {
        return TEST_FAILED;
    }
}

int main() {
    printf("read_file_test(): \n");
    if (read_file_test() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }

    printf("string_split_test(): \n");
    if (string_split_test() == TEST_SUCCESS) {
        puts("Test passed successfully\n");
    } else {
        puts("Test failed\n");
    }
}

