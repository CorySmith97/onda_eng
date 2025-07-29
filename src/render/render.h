/*
Public API for the Rendering Module.
*/

#ifndef RENDER_H
#define RENDER_H

#include "../core/core.h"
#include <epoxy/gl.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "stdbool.h"

// DATA PROTO

//
// Each backend implements their own version of this.
//
typedef void* Render;

typedef struct Mesh Mesh;
typedef struct Material Material;
typedef struct Shader Shader;
typedef struct Texture Texture;
typedef struct Vertex Vertex;
typedef struct VertexBuffer VertexBuffer;
typedef struct Model Model;

//
// FUNCTION PROTO
//

extern void r_init(GLFWwindow **window);
extern void r_clear_background(Vec4);
extern void r_begin_pass();
extern void r_end_pass();
extern void r_deinit();

extern bool r_load_shader(const char* filename, Shader* shader);
extern void r_free_shader(Shader* shader);

// Models
extern Model* r_load_model(const char* path);
extern void r_free_model(Model* model);

// Textures
extern Texture r_load_texture(const char* path);
extern void    r_free_texture(Texture*);
extern void    r_draw_texture(Texture, Vec3);

//
// IMPLEMENTATION
//

struct Texture {
    String8 name;
    i32 width;
    i32 height;
    u8 *data;
};

#endif //RENDER_H
