#define SOKOL_IMPL
#define SOKOL_METAL
#define SOKOL_NO_ENTRY
#include <sokol_gfx.h>
#include <sokol_app.h>
#include <sokol_glue.h>
#include <sokol_log.h>

static void sokol_init(void) {
    sg_setup(&(sg_desc){
        .environment = sglue_environment(),
        .logger.func = slog_func,
    });
}

static void sokol_frame(void) {
    sg_begin_pass(&(sg_pass){
        .action = {
            .colors[0] = {
                .load_action = SG_LOADACTION_CLEAR, .clear_value = { 0.25f, 0.5f, 0.7f, 1.0f }
            }
        },
        .swapchain = sglue_swapchain()
    });
    sg_end_pass();
    sg_commit();

}

void sokol_event(const sapp_event* ev) {
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

static void sokol_deinit(void) {
    sg_shutdown();
}
