#include "core.h"

/*
 * Global Allocator Interface
 */
typedef struct PageAllocator {
    void *pages;
    void *free_list;
    size_t page_count;
    size_t free_list_count;
    size_t page_current_ptr;
#ifndef CPP
    (*alloc_fn)(size_t) void*;
    (*free_fn)(void*);
#endif
} PageAllocator;

void *paalloc(PageAllocator*, size_t);
void pafree(PageAllocator*);

typedef struct ArenaAllocator {
} ArenaAllocator;

void *aaalloc(ArenaAllocator*, size_t);
void aafree(ArenaAllocator*);
