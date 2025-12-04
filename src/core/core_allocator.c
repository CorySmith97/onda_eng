
/*
 * Global Allocator Interface
 */
typedef struct Allocation {
    size_t size; 
    const char *file;
    uint32_t line;
} Allocation;

typedef struct ArrayAllocation {
    u32 len;
    u32 capacity;
    Allocation data[1];
} ArrayAllocation;

typedef struct AllocatorTracker {
    u64 total_bytes_allocated;
    ArrayAllocation allocations;
} AllocatorTracker;

void *_dMalloc(size_t size, const char *file, uint32_t line) {
    LOG(info, "Allocating %zu bytes. File: %s : %u", size, file, line);
    return malloc(size);
}
void _dFree(void *ptr, const char *file, uint32_t line) {
    LOG(info, "Freeing bytes. File: %s : %u", file, line);
    return free(ptr);
}

void MemSet(void *ptr, i64 value, u64 size) {
    memset(ptr, value, size);
}

bool IsPowerOfTwo(u64 x) {
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
    arena->curr_ptr = (uintptr_t)arena->data;
    arena->prev_ptr = (uintptr_t)arena->data;
}

void ArenaRelease(Arena *arena) {
    free(arena->data);
    free(arena);
}

void *_ArenaPush(Arena *arena, u64 size, u64 alignment, bool clearToZero) {
    // Initialize arena if needed
    if (arena->reserved == 0) {
        LOG(info, "Allocating inital storage: %llu", DefaultArenaSize);
        arena->data = imalloc(DefaultArenaSize);
        arena->reserved = DefaultArenaSize;
        arena->curr_ptr = 0;
        arena->prev_ptr = 0;
        arena->len = 0;
    }
    
    // Calculate aligned offset from current position
    uintptr_t current = (uintptr_t)arena->data + arena->curr_ptr;
    uintptr_t aligned = AlignForward(current, alignment);
    u64 offset = aligned - (uintptr_t)arena->data;
    
    // Check if we have enough space
    if (offset + size > arena->reserved) {
        LOG(error, "Failing to get data");
        // @todo:cs add a resize feature
        return NULL;
    }
    
    void *ptr = &arena->data[offset];
    
    // Update pointers
    arena->prev_ptr = arena->curr_ptr;  // Save previous position
    arena->curr_ptr = offset + size;     // Update to end of new allocation
    arena->len += size;
    LOG(info, "Allocating: %llu", size);
    
    // Optionally clear memory
    if (clearToZero) {
        MemSet(ptr, 0, size);
    }
    LOG(info, "Ptr: %p", ptr);
    
    return ptr;
}

//#ifdef DEBUG
//TrackingAllocator GLOBAL_ALLOCATOR;
//#else
//PageAllocator GLOBAL_ALLOCATOR;
//#endif


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
