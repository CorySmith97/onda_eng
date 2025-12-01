//
// Created by Cory Smith on 7/25/25.
//

#ifndef CORE_H
#define CORE_H

#define POSIX

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wmissing-braces"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef size_t usize;

#define enum8(type) u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64

#define FlagSet(n, f) ((n) |=(f))
#define FlagClear(n, f) ((n) &=-(f))
#define FlagToggle(n, f) ((n) ^=(f))
#define FlagExists(n, f) (((n) && (f)) == (f))
#define FlagEquals(n, f) (((n) == (f)))

#define KB(n) (((u64)(n)) << 10)
#define MB(n) (((u64)(n)) << 20)
#define GB(n) (((u64)(n)) << 30)
#define TB(n) (((u64)(n)) << 40)
#define Thousand(n) ((n)*1000)
#define Million(n) ((n)*1000000)
#define Billion(n) ((n)*1000000000)

#define c_panic(fmt) \
    do {    \
    fprintf(stderr, "Panic at %s:%d\n\tMessage: %s\n\n", __FILE__, __LINE__, fmt); \
    exit(1); \
    }while (0)


// ARRAYLISTS

typedef struct ArrayI32 {
    i32* data;
    u32 len;
    u32 capacity;
} ArrayI32;

typedef struct ArrayF32 ArrayF32;
typedef struct ArrayVec2 ArrayVec2;
typedef struct ArrayVec3 ArrayVec3;
typedef struct ArrayVec4 ArrayVec4;

typedef struct ArrayString {
    const char** data;
    u32 len;
    u32 capacity;
} ArrayString;

#define array_create(a, i)
#define array_reserve(a, s)
#define array_free(a)

#define array_push(a, v)                                        \
    do {                                                        \
        if (((a)->len + 1 < (a)->capacity)) {                   \
            (a)->data[(a)->len] = v;                            \
            (a)->len += 1;                                      \
        } else {                                                \
            u32 new_cap = (a)->capacity ? ((a)->capacity * 2) : 2;\
            (a)->data = realloc((a)->data, new_cap * sizeof(v));\
            (a)->capacity = new_cap;                            \
            (a)->data[(a)->len] = v;                            \
            (a)->len++;                                         \
        }                                                       \
    } while (0);

// LOGGING

#define LOG_LEVEL_GEN(ENUM) ENUM,
#define LOG_STRING_GEN(STRING) #STRING,

#define FOREACH_LOG_LEVEL(LOG_LEVEL) \
    LOG_LEVEL(warn)                  \
    LOG_LEVEL(info)                  \
    LOG_LEVEL(error)                 \
    LOG_LEVEL(debug)

#define FOREACH_LOG_LEVEL_COLOR(LOG_LEVEL)\
    LOG_LEVEL(\e[35m)                  \
    LOG_LEVEL(\e[36m)                  \
    LOG_LEVEL(\e[31m)                  \
    LOG_LEVEL(\e[33m)

enum LogLevel {
    FOREACH_LOG_LEVEL(LOG_LEVEL_GEN)
};

static const char* log_level_str[] = {
    FOREACH_LOG_LEVEL(LOG_STRING_GEN)
};

static const char* log_color_str[] = {
    FOREACH_LOG_LEVEL_COLOR(LOG_STRING_GEN)
};

#ifdef POSIX
    #define LOG(_LEVEL, _STR, ...) (printf("%s[%s]\e[0m " _STR "\n", log_color_str[_LEVEL], log_level_str[_LEVEL],  ##__VA_ARGS__))
#else
    #define LOG(_LEVEL, _STR, ...) (printf("[%s] " _STR "\n",  log_level_str[_LEVEL],  ##__VA_ARGS__))
#endif

#endif //CORE_H
