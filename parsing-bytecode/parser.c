//
// Created by fin on 29.01.19.
//

#include <malloc.h>
#include "parser.h"
#include "file.h"
#include "pars_element.h"

void load_class_and_frame(char *file_name) {
    char *text = read_file(file_name);

    size_t number_elements;
    pars_element_t *pars_elements = pars_text(text, &number_elements);
    for (int i = 0; i < number_elements; ++i) {
        switch (pars_elements[i].type_parse_element) {
            case CLASS:
                printf("class ");
                break;
            case FUNCTION:
                printf("function ");
                break;
        }

        for (int j = 0; j < pars_elements[i].number_pre_args; ++j) {
            printf("%s{\n", pars_elements[i].pre_args[j].value_arg);
        }

        for (int j = 0; j < pars_elements[i].number_args; ++j) {
            printf("%s:%s\n", pars_elements[i].args[j].name_arg, pars_elements[i].args[j].value_arg);
        }
        puts("}");
    }

    free(text);
    destructor_pars_element(pars_elements, number_elements);
}