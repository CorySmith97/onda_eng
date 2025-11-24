#include <stdio.h>
#include "core/core.h"
#define SOKOL_NO_ENTRY
#define SOKOL_IMPLEMENTATION
#define SOKOL_METAL
#include "thirdparty/sokol_app.h"
//#include "app/app.h"
//#include "render/render.h"

static_assert(sizeof(ArrayI32) == 4, "tjos should fail");

int main(void) {
    ArrayI32 a = {.data = malloc(sizeof(i32) * 5), .len = 0, .capacity = 5};
    array_push(&a, 1);
    array_push(&a, 2);
    array_push(&a, 3);
    array_push(&a, 4);
    array_push(&a, 5);
    array_push(&a, 6);

    for (int i = 0; i < a.len; i++) {
        LOG(info, "item: %u", a.data[i]);
    }

    //App app;
    //app_init(&app, backend_opengl);
    //r_init(&app.window);
    //while (!app_should_close(&app)) {
    //}
    //app_run(&app);
    //app_deinit(&app);
}
