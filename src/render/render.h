/*

Public API for the Rendering Module.
*/

#ifndef RENDER_H
#define RENDER_H

#include "../core/core.h"
#include "../app/app.h"
#include "stdbool.h"

// DATA PROTO

//
// Each backend implements their own version of this.
//
typedef void* Render;

#define WHITE

typedef enum {
    Camera_Orthographic,
    Camera_Perspective,
    Camera_2D,
} CameraTypes;

typedef struct Camera {
    Vec3 pos;
    Vec3 target;
    Vec3 up;
    f32 fov;
    CameraTypes type;
} Camera;

typedef struct Rectangle {
    i32 x;
    i32 y;
    i32 width;
    i32 height;
} Rectangle;

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

//
// FUNCTION PROTO
//

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

//
// IMPLEMENTATION
//

#endif //RENDER_H
