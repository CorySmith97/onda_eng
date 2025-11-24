/*
 * Generic Platform agnostic API function internals.
 */

#include "platform.h"
#include "sokol.c"

int app_run(PlatformDesc *desc) {
    switch (desc->backend) {
        case BACKEND_SOKOL_NATIVE: {
            sapp_run(&(sapp_desc){
                .init_cb = sokol_init,
                .frame_cb = sokol_frame,
                .event_cb = sokol_event,
                .cleanup_cb = sokol_deinit,
                .window_title = desc->title,
            });
        } break;
        case BACKEND_SOKOL_WEB: {
        } break;
    }

    return 1;
}

static KeyboardState keyboard_state;

bool isKeyPressed(int key) {
    bool pressed = false;
    if ((key > 0) && (key < MAX_KEYS)) {
        if ((keyboard_state.key_previous_state[key] == false) && 
            (keyboard_state.key_curr_state[key] == true))
        pressed = true;
    }
    return pressed;
}

bool isKeyDown(int key) {
    bool pressed = false;
    if ((key > 0) && (key < MAX_KEYS)) {
        if ((keyboard_state.key_previous_state[key] == true) && 
             (keyboard_state.key_curr_state[key] == true))
        pressed = true;
    }
    return pressed;
}

bool isKeyReleased(int key) {
    bool pressed = false;
    if ((key > 0) && (key < MAX_KEYS)) {
        if ((keyboard_state.key_previous_state[key] == true) && (keyboard_state.key_curr_state[key] == false))
        pressed = true;
    }
    return pressed;
}

void onMouseDown(int button) { 
}
void onMouseUp(int button) { 
}
void onMouseMoved(float x, float y, float dx, float dy) { 
}
void onKeyDown(int key) { 
}
void onKeyUp(int key) { 
}
void onKeyChar(uint32_t codepoint) { 
}
void onTouchBegin(float x, float y, int id) { 
}
void onTouchMoved(float x, float y, int id) { 
}
void onTouchEnded(float x, float y, int id) { 
}

void app_on_resize_fn(void) { 
}
