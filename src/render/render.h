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


typedef struct Camera Camera;
typedef struct Mesh Mesh;
typedef struct Material Material;

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
    i32 id;
    i32 width;
    i32 height;
    u8 *data;
} Texture;

typedef struct Vertex {
    f32 pos[3];
    f32 norm[3];
    f32 tex[2];
} Vertex;

typedef struct VertexBuffer VertexBuffer;
typedef struct Model Model;

//
// FUNCTION PROTO
//

extern void     r_init(App *app);
extern void     r_clear_background(Vec4);
extern void     r_begin_pass();
extern void     r_end_pass();
extern void     r_deinit();
extern void     r_update_camera();

extern bool     r_load_shader(const char* filename, Shader* shader);
extern void     r_free_shader(Shader* shader);

// Models
extern Model*   r_load_model(const char* path);
extern void     r_free_model(Model* model);
extern void     r_draw_model(Model* model, Mat4 rotation);

// Textures
extern Texture  r_load_texture(const char* path);
extern void     r_free_texture(Texture*);
extern void     r_draw_texture(Texture, Vec3);

// Drawing
extern void r_draw_rectangle( Vec3 position, Vec4 color );

//
// IMPLEMENTATION
//

#endif //RENDER_H
