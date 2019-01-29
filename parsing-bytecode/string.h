//
// Created by Fin on 15.11.2018.
//

#ifndef VM_STRING_H
#define VM_STRING_H
#include <memory.h>


char **split(const char *str, const char *delimiter, unsigned long *len);

void destructor_split_string(char **split_str, size_t size);

#endif //VM_STRING_H
