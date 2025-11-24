#ifndef PROF_H
#define PROF_H

#include <time.h>

typedef struct Section {
    String8 name;
    String8 function_name;
    struct timespec start;
    struct timespec end;
    u64 delta;
} Section;


typedef struct Profiler {
    Arena arena;
    Section *sections;
    u64 capacity;
    u64 len;
} Profiler;

Profiler *p;

void prof_init(
) {
    p = malloc(sizeof(Profiler));
    c_arena_init(&p->arena, GB(1));
}

void internal_prof_section_push(
    Section section
) {
    if (p->len++ >= p->capacity) {
        p->capacity *= 2;
        p->sections = c_arena_alloc(&p->arena, sizeof(Section) * p->capacity);
    }
}

void prof_section_begin(
    String8 name
) {

}

void prof_section_end(
    String8 name
) {}


#endif // PROF_H
