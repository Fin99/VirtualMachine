#include <stdio.h>
#include <memory.h>
#include "vm.h"
//#include "vm/parsing_bytecode/file.h"
//#include "vm/parsing_bytecode/loader.h"

#define FILE_NAME "byte.fn"
//
// Created by Fin on 04.11.2018.
//

/*frame *find_main_frame(frame *frames, int number_frames){
    frame *main = NULL;
    for (int i = 0; i < number_frames; ++i) {
        if (!strcmp("main()", frames[i].name)) {
            main = &frames[i];
        }
    }

    return main;
}

int start(const char *file_name) {
    const char *file_to_string = read_file(file_name);

    int number_frames;
    frame* frames = load_byte_code(file_to_string, &number_frames);

    frame *main = find_main_frame(frames, number_frames);

    run(main);

    //return value on top of stack
    return main->stack[0];
}

int main() {
    return start(FILE_NAME);
}
*/