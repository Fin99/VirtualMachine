//
// Created by fin on 29.01.19.
//

#include "parser.h"
#include "file.h"
#include "pars_element.h"

void load_class_and_frame(char *file_name) {
    char *text = read_file(file_name);
    pars_element_t *pars_elements = pars_text(text);

}