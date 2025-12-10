// STRINGS

// char string with known length
typedef struct String8 String8;
struct String8 {
    u8 *data;
    u64 len;
};

#define Str(str) (String8){.data = ((u8*)str), .len = sizeof((str))-1}

bool String8Compare(String8 s1, String8 s2);

String8 *c_string8_create(Arena *arena);
void     c_string8_destroy(String8 *string);

