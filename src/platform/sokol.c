#define SOKOL_IMPL
#define SOKOL_METAL
#define SOKOL_NO_ENTRY
#include <sokol_app.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>
#include <sokol_log.h>
#include <sokol_gl.h>
#define FONTSTASH_IMPLEMENTATION
#include <fontstash.h>
#define SOKOL_FONTSTASH_IMPL
#include <sokol_fontstash.h>


static void sokol_init(void* user_data) {
    //LOG(info, "Backend selected Sokol Native");
    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });
    sgl_setup(&(sgl_desc_t){});

    engineInit();

    PlatformDesc *usr = user_data;
    usr->init_fn();
}

static void sokol_frame(void* user_data) {
    PlatformDesc *usr = user_data;

    usr->frame_fn();
}

void sokol_event(const sapp_event* ev, void* user_data) {
    if (!ev) return;

    // let ImGui try to handle the event first
    //bool imgui_did_handle = simgui_handle_event(ev);
    //if (imgui_did_handle)
    //    return;

    switch (ev->type) {
        case SAPP_EVENTTYPE_MOUSE_DOWN:
            onMouseDown((int)ev->mouse_button);
            break;

        case SAPP_EVENTTYPE_MOUSE_UP:
            onMouseUp((int)ev->mouse_button);
            break;

        case SAPP_EVENTTYPE_MOUSE_MOVE:
            onMouseMoved(ev->mouse_x, ev->mouse_y, ev->mouse_dx, ev->mouse_dy);
            break;

        case SAPP_EVENTTYPE_KEY_DOWN:
            if (!ev->key_repeat)
                onKeyDown((int)ev->key_code);
            break;

        case SAPP_EVENTTYPE_KEY_UP:
            onKeyUp((int)ev->key_code);
            break;

        case SAPP_EVENTTYPE_CHAR:
            onKeyChar(ev->char_code);
            break;

        case SAPP_EVENTTYPE_TOUCHES_BEGAN:
            for (int i = 0; i < ev->num_touches; i++) {
                const sapp_touchpoint* t = &ev->touches[i];
                if (t->changed)
                    onTouchBegin(t->pos_x, t->pos_y, t->identifier);
            }
            break;

        case SAPP_EVENTTYPE_TOUCHES_MOVED:
            for (int i = 0; i < ev->num_touches; i++) {
                const sapp_touchpoint* t = &ev->touches[i];
                if (t->changed)
                    onTouchMoved(t->pos_x, t->pos_y, t->identifier);
            }
            break;

        case SAPP_EVENTTYPE_TOUCHES_ENDED:
            for (int i = 0; i < ev->num_touches; i++) {
                const sapp_touchpoint* t = &ev->touches[i];
                if (t->changed)
                    onTouchEnded(t->pos_x, t->pos_y, t->identifier);
            }
            break;

        case SAPP_EVENTTYPE_RESIZED:
            app_on_resize_fn();
            break;

        default:
            break;
    }
}

static void sokol_deinit(void* user_data) {
    sgl_shutdown();
    sg_shutdown();
}
