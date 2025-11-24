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

static void sokol_event(const sapp_event *ev) {
}

static void sokol_deinit(void) {
    sg_shutdown();
}
