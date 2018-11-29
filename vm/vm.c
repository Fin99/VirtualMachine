#include <stdio.h>
#include <memory.h>
#include "vm.h"
#include "parsing_bytecode/file.h"
#include "parsing_bytecode/loader.h"

#define FILE_NAME "byte.fn"
//
// Created by Fin on 04.11.2018.
//

frame *find_main_frame(frame *frames, int number_frames){
    frame *main = NULL;
    for (int i = 0; i < number_frames; ++i) {
        if (!strcmp("main()", frames[i].name)) {
            main = &frames[i];
        }
    }

    return main;
}

int start(const char *const file_name) {
    const char *file_to_string = read_file("byte.fn");

    int number_frames;
    frame* frames = load_byte_code(file_to_string, &number_frames);

    frame *main = find_main_frame(frames, number_frames);

    run(main);

    return main->stack[frames->pointer_stack];
}

int main() {
    return start(FILE_NAME);

//    for (int i = 0; i < number_frames; ++i) {
//        printf("%i:\n", i);
//        printf("Name - %s\n", frames[i].name);
//        printf("instruction size - %i\n", frames[i].instructions_size);
//        frame frame = frames[i];
//        for (int j = 0; j < frames[i].instructions_size; ++j) {
//            printf("\t%i: %i - %i, %p\n", frame.instructions[j].number_line, frame.instructions[j].type,
//                   frame.instructions[j].arg, frame.instructions[j].frame_arg);
//        }
//    }
//
//
//
//    printf("%i", main->stack[frames->pointer_stack]);
}
