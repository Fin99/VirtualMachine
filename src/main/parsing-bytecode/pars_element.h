//
// Created by fin on 29.01.19.
//

#ifndef VIRTUALMACHINE_PARS_ELEMENT_H
#define VIRTUALMACHINE_PARS_ELEMENT_H

enum type_parse_element {
    CLASS,
    FUNCTION
};

struct arg {
    char *name_arg;
    size_t number_values;
    char **values_arg;
};

struct pars_element {
    enum type_parse_element type_parse_element;
    struct arg *pre_args;
    size_t number_pre_args;
    struct arg *args;
    size_t number_args;
};

struct pars_element *pars_text(char *text, size_t *number_elements);

void destructor_pars_element(struct pars_element *pars_element, size_t number_elements);

#endif //VIRTUALMACHINE_PARS_ELEMENT_H
