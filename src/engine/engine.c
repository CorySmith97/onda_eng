#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "core_shaders.h"

typedef struct InternalState {
    Camera *cam;
} InternalState;

static HashMap *textures;
static InternalState *_is;

void engine_init() {
    textures = hashmap_create(sizeof(Texture));
}

void update_camera(Camera *cam) {
    _is = cam;
}

// @todo:cs this needs to open file if failed to find in the hashmap.
Texture *load_spritesheet(const char *path) {
    LOG(info, "Trying to load %s", path);
    Texture *t = malloc(sizeof(Texture));
    void *value = hashmap_get(textures, path);
    if (value != NULL) {
        return (Texture*)value;
    }

    int width, height, channels;
    stbi_uc *pixels = stbi_load(path, &width, &height, &channels, 4);
    if (pixels == NULL) {
        LOG(warn, "Failed to load %s", path);
        return NULL;
    }

    sg_image img = sg_make_image(&(sg_image_desc) {
        .type = SG_IMAGETYPE_ARRAY,
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

    return t;
}

/* The default draw sprite functions will only be compatible with the basic_atlas shader found in 
 * core shaders for the meantime.
*/
void draw_sprite(Texture *s, Vec2 pos, f32 scale, Color color) {
    vs_param_t vs_params = {
        .mvp = compute_mvp(_is->cam),
    };
    sg_apply_pipeline(s->pipe);
    sg_apply_bindings(&s->bind);
    sg_apply_uniforms(UB_vs_params, &SG_RANGE(vs_params));
    sg_draw(0, 6, 1);
}

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color);

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);
