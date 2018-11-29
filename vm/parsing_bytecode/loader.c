//
// Created by Fin on 04.11.2018.
//
#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_STACK 128
#define SIZE_LOCAL_POOL 128


int main() {
    const char *file_to_string = read_file("byte.fn");

    char **string_split = NULL;
    int number_string = split(file_to_string, '\n', &string_split);

    frame *frames = NULL;

    int number_frames = create_frames(string_split, number_string, &frames);

    for (int i = 0; i < number_frames; ++i) {
        printf("%i:\n", i);
        printf("Name - %s\n", frames[i].name);
        printf("instruction size - %i\n", frames[i].instructions_size);
        frame frame = frames[i];
        for (int j = 0; j < frames[i].instructions_size; ++j) {
            printf("\t%i: %i - %i, %p\n", frame.instructions[j].number_line, frame.instructions[j].type,
                    frame.instructions[j].arg, frame.instructions[j].frame_arg);
        }
    }

    frame *main = NULL;
    for (int i = 0; i < number_frames; ++i) {
        if (!strcmp("main()", frames[i].name)) {
            main = &frames[i];
        }
    }
    go(main);

    printf("%i", main->stack[frames->pointer_stack]);
    return 0;
}

int create_frames(char **file_split, int number_string, frame **frames) {
    int counter = counting_frames(file_split, number_string);

    *frames = malloc(sizeof(frame) * counter);

    for (int j = 0; j < counter; ++j) {
        frames[j]->stack = malloc(sizeof(int) * SIZE_STACK);

        frames[j]->size_local_pool = SIZE_LOCAL_POOL;
        frames[j]->local_pool = malloc(sizeof(int) * SIZE_LOCAL_POOL);

        frames[j]->pointer_stack = -1;
    }

    set_frames_name(file_split, number_string, frames);

    int counter_frames = 0;
    for (int i = 0; i < number_string; ++i) {
        char *string = *(file_split + i);
        if (*string != ' ') {
            instruction *instructions = NULL;
            int number_instructions = create_instructions(file_split, number_string, i, &instructions, *frames);
            i += number_instructions;
            (*frames)[counter_frames].instructions = instructions;
            (*frames)[counter_frames].instructions_size = number_instructions;

            counter_frames++;
        }
    }
    return counter;
}

int counting_frames(char **file_split, int number_string) {
    int counter = 0;
    for (int i = 0; i < number_string; ++i) {
        char *string = *(file_split + i);
        if (*string != ' ') {
            counter++;
        }
    }

    return counter;
}

void set_frames_name(char **file_split, int number_string, frame **frames) {
    int counter_frames = 0;
    for (int i = 0; i < number_string; ++i) {
        char *string = *(file_split + i);
        if (*string != ' ') {
            (*frames)[counter_frames].name = string;
            counter_frames++;
        }
    }
}

int create_instructions(char **string_split, int number_string, int number_string_name_frame, instruction **instructions,
                        frame *frames) {
    int counter_instruction = 0;
    if (number_string == number_string_name_frame) {
        return 0;
    }
    for (int i = number_string_name_frame + 1; i < number_string; ++i) {
        char *string = *(string_split + i);
        if (*string != ' ') {
            break;
        } else {
            counter_instruction++;
        }
    }

    *instructions = malloc(sizeof(instruction) * counter_instruction);
    int number_instructions = 0;

    for (int i = number_string_name_frame + 1; i < number_string; ++i) {
        char *string = *(string_split + i);
        if (*string != ' ') {
            break;
        } else {
            set_number_line_instruction(string, &(*instructions)[number_instructions]);
            set_type_instruction(string, &(*instructions)[number_instructions], frames);
            number_instructions++;
        }
    }
    return counter_instruction;
}

void set_number_line_instruction(const char *string, instruction *instruction) {

    char **split_string = NULL;
    split(string, ':', &split_string);

    instruction->number_line = (int) strtol(split_string[0], NULL, 10);
}

void set_type_instruction(char *string, instruction *ptr, frame *frames) {
    char **split_string = NULL;
    split(string, ':', &split_string);
    trim(split_string[1]);

    char **split_string1 = NULL;
    split(split_string[1], ' ', &split_string1);

    char **split_string2 = NULL;
    split(split_string1[0], '_', &split_string2);

    if (!strcmp(split_string2[0], "aload")) {
        ptr->type = ALOAD;
        ptr->arg = (int) strtol(split_string2[1], NULL, 10);
    } else if (!strcmp(split_string2[0], "invokevirtual")) {
        ptr->type = INVOKEVIRTUAL;
        int i = 0;
        while (1) {
            if (!strcmp(frames[i].name, split_string1[1])) {
                ptr->frame_arg = &frames[i];
                break;
            }
            i++;
        }
    } else if (!strcmp(split_string2[0], "istore")) {
        ptr->type = ISTORE;
        ptr->arg = (int) strtol(split_string2[1], NULL, 10);
    } else if (!strcmp(split_string2[0], "return")) {
        ptr->type = RETURN;
    } else if (!strcmp(split_string2[0], "iconst")) {
        ptr->type = ICONST;
        ptr->arg = (int) strtol(split_string2[1], NULL, 10);
    } else if (!strcmp(split_string2[0], "iload")) {
        ptr->type = ILOAD;
        ptr->arg = (int) strtol(split_string2[1], NULL, 10);
    } else if (!strcmp(split_string2[0], "ireturn")) {
        ptr->type = IRETURN;
    } else if (!strcmp(split_string2[0], "iadd")) {
        ptr->type = IADD;
    }
}

