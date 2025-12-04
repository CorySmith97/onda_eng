
// ARENA
typedef struct Arena {
    u64 reserved;
    u64 len;
    u64 prev_ptr;
    u64 curr_ptr;
    void* data;
} Arena;

#define DefaultPageSize KB((4))
#define DefaultAlignment (2*sizeof(void*))
#define DefaultArenaSize MB((1))

void ArenaClear(Arena *arena);
void ArenaRelease(Arena *arena);
void *_ArenaPush(Arena *arena, u64 size, u64 alignment, bool clearToZero);

#define ArenaPush(arena, size) _ArenaPush(arena, size, DefaultAlignment, true)
#define ArenaPushStruct(arena, type) ((type*) _ArenaPush(arena, sizeof(type), alignof(type), true))
#define ArenaPushArray(arena, count, type) ((type*) _ArenaPush(arena, (count) * sizeof(type), DefaultAlignment, true))


/*
Arena arena_alloc_init(usize size);
void  arena_init(Arena *arena, usize size);
void *arena_alloc(Arena *arena, usize size);
void  arena_reset(Arena *arena);
void  arena_deinit(Arena *arena);
void *arena_array_concat(Arena *arena, const void *a1, usize s1, const void *a2, usize s2);
char **arena_string_array_concat(Arena *arena, const char **a1, usize s1, const char **a2, usize s2);
*/

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
