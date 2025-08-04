#include <stdio.h>
#include "../app/app.h"
#include "../render/render.h"
#include <unistd.h>

int main() {
    char *buffer;

    // Call getcwd with NULL and 0 to let it allocate the buffer
    if ((buffer = getcwd(NULL, 0)) == NULL) {
        perror("Failed to get current directory");
        return 1; // Indicate an error
    } else {
        printf("Current working directory: %s\n", buffer);
        free(buffer); // Free the allocated buffer
    }
    App app;
    app_init(&app, backend_opengl);
    r_init(&app);
    Texture *t = r_texture_load("assets/testmap.png");

    while (!app_should_close(&app)) {
        Vec2 mouse_pos = app_get_mouse_position(&app);
        LOG(info, "Mouse position: (%f,%f)", mouse_pos.x, mouse_pos.y);
        r_begin_pass();
        r_clear_background((Vec4){1.0f, 1.0f, 1.0f, 1.0f});
        r_draw_texture(*t, (Vec3){0.0f, 0.0f, 0.0f}, (Vec4){0.0f, 0.0f, 1.0f, 1.0f});
        r_end_pass();
    }
    app_deinit(&app);
}
