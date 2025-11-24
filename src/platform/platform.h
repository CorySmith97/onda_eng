#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_KEYS 512

typedef struct Event Event;

typedef enum Backends {
    BACKEND_SOKOL_NATIVE,
    BACKEND_SOKOL_WEB,
} Backends;

typedef struct PlatformDesc {
    const char *title;
    int32_t width;
    int32_t height;
    void (*init_fn)(void);
    void (*frame_fn)(void);
    void (*deinit_fn)(void);
    void (*event_fn)(const Event*);
    Backends backend;
} PlatformDesc;

typedef struct KeyboardState {
    bool key_curr_state[MAX_KEYS];
    bool key_previous_state[MAX_KEYS];
    bool key_pressed[MAX_KEYS];
} KeyboardState;

int app_run(PlatformDesc*);

// IO
bool isKeyDown(int);
bool isKeyPressed(int);
bool isKeyReleased(int);
bool isMouseButtonDown(int);
bool isMouseButtonPressed(int);
bool isMouseButtonRelased(int);


// external functions you already use
void onMouseDown(int button);
void onMouseUp(int button);
void onMouseMoved(float x, float y, float dx, float dy);
void onKeyDown(int key);
void onKeyUp(int key);
void onKeyChar(uint32_t codepoint);
void onTouchBegin(float x, float y, int id);
void onTouchMoved(float x, float y, int id);
void onTouchEnded(float x, float y, int id);

void app_on_resize_fn(void);


#endif  // PLATFORM_H
