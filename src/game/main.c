#include <stdio.h>
#include "../app/app.h"
#include "../render/render.h"

int main() {
    App app;
    app_init(&app, backend_opengl);
    r_init(&app);
    while (!app_should_close(&app)) {
        r_begin_pass();
        r_clear_background((Vec4){1.0f, 0.0f, 0.0f, 1.0f});
        r_draw_rectangle((Vec3){0.0f, 0.0f, 0.0f}, (Vec4){0.0f, 0.0f, 1.0f, 1.0f});
        r_end_pass();
    }
    app_deinit(&app);
}
