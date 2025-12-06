
/** @brief Arena Allocator. Arenas are growable via a linked list type interface
*/
typedef struct Arena Arena;
struct Arena {
    u64 reserved;
    u64 len;
    u64 prev_ptr;
    u64 curr_ptr;
    void* data;
    Arena* next;
};

#define DefaultPageSize KB((4))
#define DefaultAlignment (2*sizeof(void*))
#define DefaultArenaSize MB((1))

void ArenaClear(Arena *arena);
void ArenaRelease(Arena *arena);
void *_ArenaPush(Arena *arena, u64 size, u64 alignment, bool clearToZero);

#define ArenaPush(arena, size) _ArenaPush(arena, size, DefaultAlignment, true)
#define ArenaPushStruct(arena, type) ((type*) _ArenaPush(arena, sizeof(type), alignof(type), true))
#define ArenaPushArray(arena, count, type) ((type*) _ArenaPush(arena, (count) * sizeof(type), DefaultAlignment, true))

void *_dMalloc(size_t size, const char *file, uint32_t line);
void _dFree(void *ptr, const char *file, uint32_t line);

#ifdef DEBUG
#   define imalloc(size) _dMalloc(size, __FILE__, __LINE__)
#   define ifree(ptr) _dFree(ptr, __FILE__, __LINE__)
#endif // DEBUG
