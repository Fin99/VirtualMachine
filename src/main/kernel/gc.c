#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "gc.h"
#include "stack_frame.h"

struct gc *gc = NULL;

struct gc *get_gc(){
    return gc;
}

void destructor_gc() {
    for (uint64_t i = 0; i < gc->number_objects; ++i) {
        destructor_object(gc->objects[i]);
    }
    free(gc->objects);
    free(gc);
}

void init_gc() {
    if (gc != NULL) {
        destructor_gc();
    }
    gc = malloc(sizeof(struct gc));

    gc->objects = NULL;
    gc->number_objects = 0;
    gc->heap_size = 0;
}

int get_index_object(struct object *object){
    for (int i = 0; i < gc->number_objects; ++i) {
        if(object == gc->objects[i]){
            return i;
        }
    }
    return 0; //error
}

void mark_root(bool *mark) {
    struct frame **frames = get_stack_frame()->frames;
    int number_frames = get_stack_frame()->number_frames;

    for (int i = 0; i < number_frames; ++i) {
        struct frame *frame = frames[i];
        for (int j = 0; j <= frame->index_first_element_work_stack; ++j) {
            if (frame->is_work_stack_element_object[j]) {
                int index = get_index_object((struct object *)frame->work_stack[j]);
                mark[index] = true;
            }
        }

        for (int j = 0; j < LOCAL_POOL_SIZE_MAX; ++j) {
            if (frame->is_local_pool_element_object[j]) {
                int index = get_index_object((struct object *)frame->local_pool[j]);
                mark[index] = true;
            }
        }
    }
}

void mark_object_tree(bool *mark, struct object *object) {
    mark[get_index_object(object)] = true;
    for (int j = 0; j < object->class->number_fields; ++j) {
        if (object->is_field_object[j]) {
            struct object *embedded = (struct object *) object->fields[j];
            if (!mark[get_index_object(embedded)]) {
                mark_object_tree(mark, embedded);
            }
        }
    }
}

void mark_tree(bool *mark) {
    bool *copy_mark = calloc(1, sizeof(bool) * gc->number_objects);
    memcpy((void *) copy_mark, mark, sizeof(bool) * gc->number_objects);

    for (int i = 0; i < gc->number_objects; ++i) {
        if (copy_mark[i]) {
            struct object *object = gc->objects[i];
            mark_object_tree(mark, object);
        }
    }


    free(copy_mark);
}

bool *mark() {
    bool *mark = calloc(1, sizeof(bool) * gc->number_objects);
    mark_root(mark);

    if (DEBUG || DEBUG_HEAP) {
        puts("Snap root");
        for (int i = 0; i < gc->number_objects; ++i) {
            printf("%i: %p - %s\n", i, gc->objects[i], mark[i] ? "true" : "false");
        }
    }

    mark_tree(mark);

    if (DEBUG || DEBUG_HEAP) {
        puts("Snap tree");
        for (int i = 0; i < gc->number_objects; ++i) {
            printf("%i: %p - %s\n", i, gc->objects[i], mark[i] ? "true" : "false");
        }
    }

    return mark;
}

void sweep(const bool *mark) {
    for (int i = 0; i < gc->number_objects; ++i) {
        if (!mark[i]) {
            gc->heap_size -= sizeof(struct object) + sizeof(var) * gc->objects[i]->class->number_fields;

            destructor_object(gc->objects[i]);
            gc->objects[i] = NULL;
        }
    }
}

void compact() {
    for (int i = 0; i < gc->number_objects; ++i) {
        if (gc->objects[i] == NULL) {
            if (i != gc->number_objects - 1) {
                if (i == 0) {
                    gc->objects[0] = gc->objects[1];
                    if (i + 1 != gc->number_objects - 1)
                        memmove(gc->objects[1], gc->objects[2], (size_t) (gc->number_objects - i - 2));
                } else {
                    memmove(gc->objects[i], gc->objects[i + 1], (size_t) (gc->number_objects - i - 1));
                }
            }

            gc->number_objects--;
            gc->objects = realloc(gc->objects, (size_t) ((gc->number_objects) * 8));
        }
    }
}

void start_gc() {
    bool *mark_result = mark();

    sweep(mark_result);

    compact();

    if (DEBUG || DEBUG_HEAP) {
        puts("Snap after compact");
        for (int i = 0; i < gc->number_objects; ++i) {
            printf("%i: %p\n", i, gc->objects[i]);
        }
    }

    free(mark_result);
}

bool check_gc(struct class *class) {
    uint64_t size_object = sizeof(struct object) + sizeof(var) * class->number_fields;

    if (true) {
        start_gc();
    }

    if (size_object + gc->heap_size > MAX_HEAP_SIZE) {
        return false;
    }

    if(DEBUG || DEBUG_HEAP){
        printf("Max heap size: %i. Heap size: %lu. Load: %lu%%\n", MAX_HEAP_SIZE,
               gc->heap_size, (gc->heap_size + size_object) * 100 / MAX_HEAP_SIZE);
    }

    return true;
}

var new_object(struct class *class) {
    if (check_gc(class)) {
        gc->objects = realloc(gc->objects, (size_t) ((gc->number_objects + 1) * 8));
        gc->heap_size += sizeof(struct object) + sizeof(var) * class->number_fields;

        struct object *object = constructor_object(class);

        gc->objects[gc->number_objects++] = object;

        if (DEBUG || DEBUG_HEAP) {
            puts("After create object");
            free(mark());
        }

        return (var) object;
    } else {
        return (var) NULL; //error
    }
}
