/*
 * Generic Platform agnostic API function internals.
 */

#include "platform.h"
#include "sokol.c"

int app_run(PlatformDesc *desc) {
    LOG(info, "Beginning to run application");
    switch (desc->backend) {
        case BACKEND_SOKOL_NATIVE: {
            LOG(info, "Backend selected Sokol Native");
            sapp_run(&(sapp_desc){
                .user_data = desc,
                .init_userdata_cb = sokol_init,
                .frame_userdata_cb = sokol_frame,
                .event_userdata_cb = sokol_event,
                .cleanup_userdata_cb = sokol_deinit,
                .window_title = desc->title,
            });
        } break;
        case BACKEND_SOKOL_WEB: {
            LOG(info, "Backend selected Sokol Web");
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
    if (keyboard_state.key_curr_state[key] == true) {
        keyboard_state.key_previous_state[key] = true;
    }
    keyboard_state.key_curr_state[key] = true;
}
void onKeyUp(int key) { 
    keyboard_state.key_curr_state[key] = false;
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
