#include "render.h"

typedef struct CommandBuffer CommandBuffer;
struct CommandBuffer {

};

struct Render {
    Arena arena;
};

Render *r;

void r_init(
    GLFWwindow **window
) {
    r = (Render *)malloc(sizeof(Render));
    c_arena_init(&r->arena, GB(1));

}

void r_clear_background(Vec4);
void r_begin_pass();
void r_end_pass();
void r_deinit();
void r_update_camera();
