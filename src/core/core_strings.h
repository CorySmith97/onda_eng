// STRINGS

// char string with known length
typedef struct String8 String8;
struct String8 {
    u8 *data;
    u64 len;
};


String8 *c_string8_create(Arena *arena);
void     c_string8_destroy(String8 *string);

