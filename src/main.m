#define SOKOL_NO_ENTRY

// Header Includes
#include "platform/platform.h"


// C Includes
#include "platform/platform.c"

int main() {
    app_run(&(PlatformDesc){
            .title = "window",
            .backend = BACKEND_SOKOL_NATIVE,
    });
}

//sapp_desc sokol_main(int argc, char* argv[]) {
//    (void)argc; (void)argv;
//    return (sapp_desc){
//    .init_cb = init,
//    .frame_cb = frame,
//    .cleanup_cb = cleanup,
//    .width = 640,
//    .height = 480,
//    .window_title = "Triangle",
//    .icon.sokol_default = true,
//    .logger.func = slog_func,
//    };
//}
