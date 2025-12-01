
/*
 * Global Allocator Interface
 */
void MemSet(void *ptr, i64 value, u64 size) {
    memset(ptr, value, size);
}

bool IsPowerOfTwo(u64 align) {
    return (x & (x-1)) == 0;
}

u64 AlignForward(u64 ptr, u64 align) {
    u64 p, a, modulo;

    assert(IsPowerOfTwo(align));
    p = ptr;
    a = (u64)align;

    modulo = p & (a-1);

    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

void ArenaClear(Arena *arena) {
    arena->curr_ptr = 0;
}

void ArenaRelease(Arena *arena) {
    free(arena->data);
    free(arena);
}

void *_ArenaPush(Arena *arena, u64 size, u64 alignment, bool clearToZero) {
    uintptr_t current = arena->data + arena->curr_ptr;
    uintptr_t offset = AlignForward(current, alignment);
    offset -= (u64)arena->data;
    
    if (arena->reserved == 0) {
        arena->data = malloc(DefaultArenaSize);
        arena->reserved = DefaultArenaSize;
    }

    if (offset+size <= arena->reserved) {
        void *ptr = &arena->data[offset];
        arena->prev_ptr = (u64)offset;
        arena->curr_ptr = (u64)offset+size;

        MemSet(ptr, 0, size);
        return ptr;
    } else {
        // @todo:cs add a resize feature
        return NULL;
    }
}

#ifdef DEBUG
TrackingAllocator GLOBAL_ALLOCATOR;
#else
PageAllocator GLOBAL_ALLOCATOR;
#endif


void *paalloc(PageAllocator*, size_t);
void pafree(PageAllocator*);

void *aaalloc(ArenaAllocator*, size_t);
void aafree(ArenaAllocator*);


/*
Arena c_arena_alloc_init(
    usize size
) {
    return (Arena){.data = malloc(size), .size = size, .current = 0};
}

void c_arena_init(Arena *arena, usize size) {
    arena->size = size;
    arena->current = 0;
    arena->data = malloc(size);
}

void *c_arena_alloc(
    Arena *arena,
    usize size
) {
    if (arena->current + size > arena->size) {
        return NULL;
    }
    void *ptr = arena->data + arena->current;
    arena->current += size;
    return ptr;
}

void c_arena_reset(
    Arena *arena
) {
    arena->current = 0;
}

void c_arena_deinit(
    Arena *arena
) {
    free(arena->data);
}

void *c_arena_array_concat(
    Arena *arena,
    const void *a1, usize s1,
    const void *a2, usize s2
) {
    void *ret = c_arena_alloc(arena, (usize)s1 + s2);
    memcpy(ret, a1, s1);
    memcpy(ret + s1, a2, s2);

    return ret;
}


char **c_arena_string_array_concat(
    Arena *arena,
    const char **a1, usize s1,
    const char **a2, usize s2
) {
    usize total = s1 + s2;
    char **ret = c_arena_alloc(arena, total * sizeof(char*));
    if (!ret) return NULL;

    // Copy pointers from first array
    memcpy(ret, a1, s1 * sizeof(char*));
    // Copy pointers from second array
    memcpy(ret + s1, a2, s2 * sizeof(char*));

    return ret;
}
*/
