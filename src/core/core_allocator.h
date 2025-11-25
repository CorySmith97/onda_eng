
typedef struct PageAllocator {
    void *pages;
    void *free_list;
    size_t page_count;
    size_t free_list_count;
    size_t page_current_ptr;
#ifdef __cplusplus
    (*alloc_fn)(size_t) void*;
    (*free_fn)(void*);
#endif
} PageAllocator;

typedef struct ArenaAllocator {
} ArenaAllocator;
