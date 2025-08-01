#include <stdio.h>
#include "app/app.h"
#include "render/render.h"

int main(void) {
    App app;
    app_init(&app);
    r_init(&app.window);
    while (!app_should_close()) {
    }
    app_run(&app);
    app_deinit(&app);
}
