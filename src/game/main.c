#include <stdio.h>
#include "../app/app.h"
#include "../render/render.h"

int main() {
    App app;
    app_init(&app, backend_opengl);
    r_init(&app);
    while (!app_should_close(&app)) {
        r_begin_pass();
        r_end_pass();
    }
    app_deinit(&app);
}
