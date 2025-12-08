#ifndef PROF_H
#define PROF_H

#include <time.h>

typedef struct {
    String8 name;
    uint64_t start_ns;
    uint64_t end_ns;
    uint64_t delta_ns;
} Section;

typedef struct ArraySection {
    Section *data;
    u64 capacity;
    u64 len;
} ArraySection;

typedef struct Profiler {
    Arena arena;
    ArraySection sections;
} Profiler;

Profiler profiler;

#ifdef DEBUG
#   define SectionStart(_S) _internal_section_start((Str(_S)))
#   define SectionEnd(_S) _internal_section_end((Str(_S)))
#else
#   define SectionStart(_S)
#   define SectionEnd(_S)
#endif

static uint64_t timespec_to_ns(struct timespec ts) {
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

static void _internal_section_start(String8 str) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    Section d = {
        .name     = str,
        .start_ns = timespec_to_ns(ts),
        .end_ns   = 0,
        .delta_ns = 0,
    };
    array_push(&profiler.sections, d);
}

static void _internal_section_end(String8 str) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t now_ns = timespec_to_ns(ts);
    
    for (int i = profiler.sections.len - 1; i >= 0; i--) {
        Section *sec = &profiler.sections.data[i];
        if (String8Compare(str, sec->name) && sec->end_ns == 0) { 
            sec->end_ns   = now_ns;
            sec->delta_ns = now_ns - sec->start_ns;
            break;
        }
    }
}

void ResetProf() {
    profiler.sections.len = 0;
}


#endif // PROF_H
