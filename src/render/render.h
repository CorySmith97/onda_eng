/*

Public API for the Rendering Module.
*/

#ifndef RENDER_H
#define RENDER_H

// DATA PROTO

#define WHITE

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
    u32 id;
    i32 width;
    i32 channels;
    i32 height;
} Texture;

typedef struct Mesh {
};

typedef struct Model Model;

typedef struct Sprite {
    u32 id;
} Sprite;

//
// FUNCTION PROTO
//

SpritesheetId load_spritesheet(const char *path);

/** @brief Drawing function for a single sprite. The sprite for this is the entire image.
 */
void draw_sprite(Texture s, vec2 pos, f32 scale, Color color);

/** @brief Drawing function for a single sprite from a spritesheet.
 *      src is the starting position of the sprite. size is the 
 *      width/height of the sprite as found on the spritesheet.
 */
void draw_sprite_ex(Texture s, vec2 pos, vec2 src, vec2 size, f32 scale, Color color);

/** @brief Same idea as the draw_sprite_ex, but allows for rotation.
 */
void draw_sprite_ex(Texture s, vec2 pos, vec2 src, vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);

/*
extern void     r_init(App *app);
extern void     r_clear_background(Vec4);
extern void     r_begin_pass();
extern void     r_end_pass();
extern void     r_deinit();

extern bool     r_load_shader(const char* filename, Shader* shader);
extern void     r_free_shader(Shader* shader);

// Camera
extern void     r_update_camera();

// Models
extern Model*   r_load_model(const char* path);
extern void     r_free_model(Model* model);
extern void     r_draw_model(Model* model, Mat4 rotation);

// Textures
extern Texture* r_texture_load(const char* path);
extern void     r_texture_laod(Texture*);
extern void     r_draw_texture(Texture, Vec3, Vec4);

// Drawing
extern void r_draw_rectangle(Vec3 position, Vec4 color);
*/

//
// IMPLEMENTATION
//

#endif //RENDER_H
