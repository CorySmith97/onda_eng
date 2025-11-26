#ifndef ENGINE_H
#define ENGINE_H
/*
Engine runtime API
*/
#define SOKOL_METAL
#include <sokol_gfx.h>
#include <sokol_app.h>
#include <sokol_glue.h>
#include <sokol_log.h>

typedef enum {
    CAMERA_ORTHOGRAPHIC,
    CAMERA_PERSPECTIVE,
    CAMERA_2D,
} CameraTypes;

typedef struct Camera {
    Vec3 pos;
    Vec3 target;
    Vec3 up;
    f32 fov;
    CameraTypes type;
} Camera;

typedef struct RectangleI32 {
    i32 x;
    i32 y;
    i32 width;
    i32 height;
} RectangleI32;

typedef struct RectangleF32 {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
} RectangleF32;

typedef struct Shader {
	i32 id;
} Shader;

typedef struct Texture {
    sg_bindings bind;
    sg_pipeline pipe;
    sg_image img;
    sg_view view;
    sg_sampler smp;
} Texture;

typedef struct Mesh {
};

typedef struct Model Model;

typedef struct Sprite {
    u32 id;
} Sprite;

typedef struct Color {
    u8 r, g, b, a;
} Color;

//
// FUNCTION PROTO
//

void engine_init(void);
Texture *load_spritesheet(const char *path);

/** @brief Drawing function for a single sprite. The sprite for this is the entire image.
 */
void draw_sprite(Texture *s, Vec2 pos, f32 scale, Color color);

/** @brief Drawing function for a single sprite from a spritesheet.
 *      src is the starting position of the sprite. size is the 
 *      width/height of the sprite as found on the spritesheet.
 */
//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color);

/** @brief Same idea as the draw_sprite_ex, but allows for rotation.
 */
//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);


#endif  // ENGINE_H
