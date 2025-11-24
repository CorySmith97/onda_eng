#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>

#define MAX_KEYS 512

typedef struct KeyboardState {
    bool keyboard_pressed[MAX_KEYS];
    bool keyboard_pressed[MAX_KEYS];
} KeyboardState;

typedef struct PlatformDesc {
} PlatformDesc;

int app_run(PlatformDesc);

#endif  // PLATFORM_H
