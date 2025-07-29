#include <stdio.h>
#include "../app/app.h"

int main() {
    App app;
    app_init(&app, backend_opengl);
    app_run(&app);
    app_deinit(&app);
    printf("Hello world\n");
}
