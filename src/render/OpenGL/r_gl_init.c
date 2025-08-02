#include "GLFW/glfw3.h"
#include "../render.h"
#include <OpenGL/gl.h>
#include <stdbool.h>
#include <stdio.h>

const char *vs_shader = "#version 410 core\n"
    "layout (location = 0) in vec3 a_pos;\n"
    "layout (location = 1) in vec4 a_color;\n"
    "out vec4 v_color;\n"
    "void main() {\n"
    "   gl_Position = vec4(a_pos, 1.0);\n"
    "   v_color = a_color;\n"
    "}\0";

const char *fs_shader = "#version 410 core\n"
    "in vec4 v_color;\n"
    "out vec4 out_color;\n"
    "void main() {\n"
    "   out_color = v_color;\n"
    "}\0";

typedef struct DrawCall {
    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 vert_count;
} DrawCall;

typedef struct ArrayDrawCall {
    DrawCall* data;
    u32 len;
    u32 capacity;
} ArrayDrawCall;

ArrayDrawCall* r_array_draw_calls_init(
    Arena *arena,
    u32 capacity
) {
    ArrayDrawCall *arr = c_arena_alloc(arena, sizeof(ArrayDrawCall*));
    arr->data = c_arena_alloc(arena, sizeof(DrawCall*) * capacity);
    arr->capacity = capacity;
    arr->len = 0;
    return arr;
}

ArrayDrawCall* r_array_draw_calls_push(
    Arena* arena,
    ArrayDrawCall* array_draw_calls
) {
    return NULL;
}


typedef struct CommandBuffer CommandBuffer;
struct CommandBuffer {
    ArrayDrawCall draw_calls;
};



struct Render {
    Arena arena;
    Rectangle viewport;
    bool drawing_enabled;
    CommandBuffer cmdbuf;
};

struct Render *r;

void r_init(
    App *app
) {
    r = (struct Render *)malloc(sizeof(struct Render));
    c_arena_init(&r->arena, GB(1));
    glfwMakeContextCurrent(app->window);
    r->cmdbuf.draw_calls = *r_array_draw_calls_init(&r->arena, 10);

    glViewport(0, 0, app->width, app->height);

    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    u32 frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex_shader, 1, &vs_shader, NULL);
    glShaderSource(frag_shader, 1, &fs_shader, NULL);
    glCompileShader(vertex_shader);
    glCompileShader(frag_shader);

    u32 shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        LOG(error, "Vertex shader compilation failed: %s", infoLog);
    }
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
        LOG(error, "Freag shader compilation failed: %s", infoLog);
    }


    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        LOG(error, "shader program failed: %s", infoLog);
    }
    glUseProgram(shader_program);
}

void r_clear_background(Vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void r_begin_pass() {
    r->drawing_enabled = true;
}

void r_end_pass() {
    r->drawing_enabled = false;
    for (u32 i = 0; i < r->cmdbuf.draw_calls.len; i++) {
        DrawCall dc = r->cmdbuf.draw_calls.data[i];
        //LOG(info, "draw call %i, %i", dc.vao, dc.vert_count);
        glBindVertexArray(dc.vao);
        glDrawElements(GL_TRIANGLES, dc.vert_count, GL_UNSIGNED_INT, NULL);
    }
    r->cmdbuf.draw_calls.len = 0;
}

void r_deinit() {
    c_arena_deinit(&r->arena);
    free(r);
}

void r_draw_rectangle(
    Vec3 position,
    Vec4 color
) {
    DrawCall *dc = c_arena_alloc(&r->arena, sizeof(DrawCall));

    f32 vertices[] = {
        -0.1f, -0.1f, 0.0f, color.x, color.y, color.z, color.w,
        0.1f, -0.1f, 0.0f, color.x, color.y, color.z, color.w,
        0.1f, 0.1f, 0.0f, color.x, color.y, color.z, color.w,
        -0.1f, 0.1f, 0.0f, color.x, color.y, color.z, color.w,
    };

    u32 indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    u32 vbo;
    u32 ebo;
    u32 vao;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLsizei stride = 7 * sizeof(f32);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(f32) * 3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    dc->vert_count = 6;
    dc->vao = vao;
    r->cmdbuf.draw_calls.len += 1;
    r->cmdbuf.draw_calls.data[0] = *dc;

}

void internal_r_vert_attributes() {
    return;
}


void r_update_camera();
