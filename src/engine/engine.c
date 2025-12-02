#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "core_shaders.h"

typedef struct InternalState {
    Arena *frame_arena;
    Camera *cam;
} InternalState;

static HashMap *textures;
static InternalState _is = {0};
FONScontext* fons_context;
int font;

void engine_init() {
    LOG(info, "Engine Initialized");
    textures = hashmap_create(sizeof(Texture));

    fons_context = sfons_create(&(sfons_desc_t) {
        .width = 512,
        .height = 512,
    });

    font = fonsAddFont(fons_context, "sans", "data/fonts/Cyber_Time.ttf");
}

void update_camera(Camera *cam) {
    _is.cam = cam;
}

// @todo:cs this needs to open file if failed to find in the hashmap.
Texture *load_spritesheet(const char *path) {
    Texture *t = malloc(sizeof(Texture));
    void *value = hashmap_get(textures, path);
    if (value != NULL) {
        return (Texture*)value;
    }

    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    stbi_uc *pixels = stbi_load(path, &width, &height, &channels, 4);
    if (pixels == NULL) {
        LOG(warn, "Failed to load %s", path);
        return NULL;
    }

    t->width = width;
    t->height = height;

    sg_image img = sg_make_image(&(sg_image_desc) {
        .type = SG_IMAGETYPE_2D,
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
        .data.mip_levels[0] = {
            .ptr = pixels,
            .size = (size_t)(width * height * 4),
        },
    });
    stbi_image_free(pixels);

    // a texture view for the image
    sg_view tex_view = sg_make_view(&(sg_view_desc){
        .texture = { .image = img },
        .label = "array-texture-view"
    });

    // a sampler object
    sg_sampler smp = sg_make_sampler(&(sg_sampler_desc){
        .min_filter = SG_FILTER_LINEAR,
        .mag_filter = SG_FILTER_LINEAR,
        .label = "sampler",
    });

    f32 verts[16] = {
        0, 1, 0.0, 1.0,
        1, 1, 1.0, 1.0,
        1, 0, 1.0, 0.0,
        0, 0, 0.0, 0.0,
    };

    u16 indices[6] = {
        0, 1, 2,
        0, 2, 3,
    };

    sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
        .data = SG_RANGE(verts),
    });
    sg_buffer ibuf = sg_make_buffer(&(sg_buffer_desc) {
        .usage.index_buffer = true,
        .data = SG_RANGE(indices),
    });

    t->pipe = sg_make_pipeline(&(sg_pipeline_desc){
        .layout = {
            .attrs = {
                [ATTR_basic_atlas_position].format = SG_VERTEXFORMAT_FLOAT2,
                [ATTR_basic_atlas_uv_coords].format = SG_VERTEXFORMAT_FLOAT2,
            },
        },
        .shader = sg_make_shader(basic_atlas_shader_desc(sg_query_backend())),
        .index_type = SG_INDEXTYPE_UINT16,
    });

    t->bind = (sg_bindings) {
        .vertex_buffers[0] = vbuf,
        .index_buffer = ibuf,
        .views[VIEW_tex2d] = tex_view,
        .samplers[SMP_smp] = smp,
    };

    hashmap_put(textures, path, t);

    LOG(info, "Loaded texture at: %s", path);
    return t;
}

Mat4 projection(Camera *cam) {
    f32 halfWidth = sapp_widthf() / 2.0f * cam->zoom_factor;
    f32 halfHeight = sapp_heightf() / 2.0f * cam->zoom_factor;
    
    Mat4 proj = c_mat4_ortho(
        0, 
        1,
        0.0, 
        1,
        -1.0, 
        1.0
    );

    return proj;
}

Mat4 view(Camera *cam) {
    return c_mat4_trans(cam->pos.x, cam->pos.y, cam->pos.z);
}

Mat4 compute_mvp(Camera *cam, f32 scalar) {
    switch (cam->type) {
        case CAMERA_2D: {
            Mat4 proj = projection(cam);
            Mat4 view_mat = view(cam);
            Mat4 model = c_mat4_identity();
            return c_mat4_mul(c_mat4_mul(proj, view_mat), model);
        } break;
        default: {}
    }
    return c_mat4_identity();
}

void beginTextDrawing() {
    sgl_defaults();
    sgl_matrix_mode_projection();
    sgl_load_identity();
    sgl_ortho(0.0f, sapp_widthf(), sapp_heightf(), 0.0f, 1.0f, -1.0f);
}
void endTextDrawing() {
    sfons_flush(fons_context);
    sgl_draw();
}

void drawFps() {
    float dx = 10, dy = 0;
    u32 white = sfons_rgba(255,255,255,255);
    u32 brown = sfons_rgba(192,128,0,128);

    fonsSetFont(fons_context, font);
    fonsSetSize(fons_context, 124.0f);
    fonsSetColor(fons_context, white);
    fonsDrawText(fons_context, dx,dy + 124,"The big ", NULL);

    fonsSetSize(fons_context, 24.0f);
    fonsSetColor(fons_context, brown);
    fonsDrawText(fons_context, dx,dy,"brown fox", NULL);
}

/* The default draw sprite functions will only be compatible with the basic_atlas shader found in 
 * core shaders for the meantime.
*/
void draw_sprite(Texture *s, Vec2 pos, f32 scale, Color color) {
    f32 tWidth = s->width;
    f32 tHeight = s->height;

    Mat4 model = c_mat4_scale(scale, scale, scale);
    vs_params_t vs_params = {
        .mvp = c_mat4_mul(compute_mvp(_is.cam, scale), model),
        .atlas_size = {tWidth, tHeight},
        .sprite_rec = {pos.x, pos.y, tWidth, tHeight},
    };
    sg_apply_pipeline(s->pipe);
    sg_apply_bindings(&s->bind);
    sg_apply_uniforms(UB_vs_params, &SG_RANGE(vs_params));
    sg_draw(0, 6, 1);
}

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color);
void drawSpriteEx( Texture *s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color) {
    f32 tWidth = s->width;
    f32 tHeight = s->height;
    Mat4 model = c_mat4_scale(scale, scale, 1.0);
    vs_params_t vs_params = {
        .mvp = c_mat4_mul(compute_mvp(_is.cam, scale), model),
        .atlas_size = {tWidth, tHeight},
        .sprite_rec = {src.x, src.y, src.x + size.x, src.y + size.y},
    };
    sg_apply_pipeline(s->pipe);
    sg_apply_bindings(&s->bind);
    sg_apply_uniforms(UB_vs_params, &SG_RANGE(vs_params));
    sg_draw(0, 6, 1);
}

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);
