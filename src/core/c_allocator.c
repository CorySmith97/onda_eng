#include "core.h"

/*
 * Global Allocator Interface
 */
typedef struct Allocator {
    void *pages;
    void *free_list;
    size_t page_count;
    size_t free_list_count;
    size_t page_current_ptr;
#ifndef CPP
    (*alloc_fn)(size_t) void*;
    (*free_fn)(void*);
#endif
} Allocator;

void *alloc(Allocator*, size_t);
void free(Allocator*);
