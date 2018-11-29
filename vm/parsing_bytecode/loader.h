//
// Created by Fin on 04.11.2018.
//

#ifndef VM_LOADER_H
#define VM_LOADER_H

#include "../frame.h"
#include "string.h"
#include "file.h"

frame *load_byte_code(const char *const file_to_string, int *number_frames);

int create_frames(char **file_split, int number_string, frame **frames);

int counting_frames(char **file_split, int number_string);

void set_frames_name(char **file_split, int number_string, frame **frames);

int create_instructions(char **string_split, int number_string, int number_string_name_frame,
                        instruction **instructions, frame *frames);

void set_number_line_instruction(const char *string, instruction *instruction);

void set_type_instruction(char *string, instruction *ptr, frame *frames);

#endif //VM_LOADER_H
