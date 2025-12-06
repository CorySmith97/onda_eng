#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "core_shaders.h"

#define MAXSPRITESINBATCH 1000

typedef struct InternalState {
    Arena *frame_arena;
    Camera *cam;
} InternalState;

/* STATIC VARS */

static HashMap *textures;
static InternalState _is = {0};
FONScontext* fons_context;
int font;

/* STATE FUNCTIONS */

void engineInit() {
    LOG(info, "Engine Initialized");
    textures = hashmap_create(sizeof(Texture));

    fons_context = sfons_create(&(sfons_desc_t) {
        .width = 512,
        .height = 512,
    });

    font = fonsAddFont(fons_context, "sans", "data/fonts/Cyber_Time.ttf");
}


/* UTIL FUNCTIONS */


void update_camera(Camera *cam) {
    _is.cam = cam;
}

// @todo:cs this needs to open file if failed to find in the hashmap.
Texture *loadSpritesheet(const char *path) {
    Texture *t = imalloc(sizeof(Texture));
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

    t->sprites = imalloc(sizeof(ArraySprite));
    t->sprites->len = 0;
    t->sprites->capacity = 100;
    t->sprites->data = imalloc(sizeof(Sprite) * 100);

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
        .min_filter = SG_FILTER_NEAREST,
        .mag_filter = SG_FILTER_NEAREST,
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
    sg_buffer streambuf = sg_make_buffer(&(sg_buffer_desc){
        .usage.stream_update = true,
        .size = sizeof(Sprite) * MAXSPRITESINBATCH,
    });
    sg_buffer ibuf = sg_make_buffer(&(sg_buffer_desc) {
        .usage.index_buffer = true,
        .data = SG_RANGE(indices),
    });

    t->pipe = sg_make_pipeline(&(sg_pipeline_desc){
        .layout = {
            .buffers[1].step_func = SG_VERTEXSTEP_PER_INSTANCE,
            .attrs = {
                [ATTR_basic_atlas_position] ={ .format = SG_VERTEXFORMAT_FLOAT2, .buffer_index = 0},
                [ATTR_basic_atlas_uv_coords] = {.format = SG_VERTEXFORMAT_FLOAT2, .buffer_index = 0},
                [ATTR_basic_atlas_sprite_pos] = { .format = SG_VERTEXFORMAT_FLOAT3, .buffer_index = 1},
                [ATTR_basic_atlas_sprite_rec] = { .format = SG_VERTEXFORMAT_FLOAT4, .buffer_index = 1},
            },
        },
        .shader = sg_make_shader(basic_atlas_shader_desc(sg_query_backend())),
        .index_type = SG_INDEXTYPE_UINT16,
        .colors[0].blend = {
            .enabled = true,
            .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
            .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            .op_rgb = SG_BLENDOP_ADD,
            .src_factor_alpha = SG_BLENDFACTOR_ONE,
            .dst_factor_alpha = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            .op_alpha = SG_BLENDOP_ADD,
        },
    });

    t->bind = (sg_bindings) {
        .vertex_buffers[0] = vbuf,
        .vertex_buffers[1] = streambuf,
        .index_buffer = ibuf,
        .views[VIEW_tex2d] = tex_view,
        .samplers[SMP_smp] = smp,
    };

    hashmap_put(textures, path, t);

    LOG(info, "Loaded texture at: %s", path);
    return t;
}

/* CAMERA */

Vec2 mouseToWorldPosition(Camera cam, Vec2 mouse) {
    float screen_w = sapp_widthf();
    float screen_h = sapp_heightf();

    // how much of the world we see
    float half_w = screen_w * 0.5f * cam.zoom_factor;
    float half_h = screen_h * 0.5f * cam.zoom_factor;

    // convert mouse from pixel coords → normalized 0..1
    float nx = mouse.x / screen_w;
    float ny = mouse.y / screen_h;

    // convert to NDC (clip space): -1 .. +1
    float ndc_x = nx * 2.0f - 1.0f;
    float ndc_y = 1.0f - ny * 2.0f; // flip because screen Y grows downward

    // convert NDC -> world
    float world_x = cam.pos.x + ndc_x * half_w;
    float world_y = cam.pos.y + ndc_y * half_h;

    return (Vec2){ world_x, world_y };
}

Mat4 projection(Camera *cam) {
    f32 halfWidth = sapp_widthf() / 2.0 * cam->zoom_factor;
    f32 halfHeight = sapp_heightf() / 2.0 * cam->zoom_factor;
    
    Mat4 proj = Mat4Ortho(
        -halfWidth,
        halfWidth,
        -halfHeight, 
        halfHeight, 
        -1.0, 
        1.0
    );

    return proj;
}

Mat4 view(Camera *cam) {
    return Mat4Trans(cam->pos.x, cam->pos.y, cam->pos.z);
}

Mat4 compute_mvp(Camera *cam) {
    switch (cam->type) {
        case CAMERA_2D: {
            Mat4 proj = projection(cam);
            Mat4 view_mat = view(cam);
            Mat4 model = Mat4Identity();
            return Mat4Mul(Mat4Mul(proj, view_mat), model);
        } break;
        default: {}
    }
    return Mat4Identity();
}

/* DRAWING FUNCTIONS */

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

void fonsPrintf(FONScontext* fs, float x, float y, const char* fmt, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    fonsDrawText(fs, x, y, buffer, NULL);
}

void drawCameraCoords(Camera *cam) {
    float dx = 10, dy = 10;
    u32 white = sfons_rgba(255,255,255,255);
    u32 brown = sfons_rgba(192,128,0,128);

    fonsSetFont(fons_context, font);
    fonsSetSize(fons_context, 24.0f);
    fonsSetColor(fons_context, white);
    fonsPrintf(fons_context, dx, dy, "%f, %f, %f", cam->pos.x, cam->pos.y, cam->pos.z);
}

void drawFps() {
    float dx = 10, dy = 0;
    u32 white = sfons_rgba(255,255,255,255);
    u32 brown = sfons_rgba(192,128,0,128);

    fonsSetFont(fons_context, font);
    fonsSetSize(fons_context, 24.0f);
    fonsSetColor(fons_context, white);
    fonsPrintf(fons_context, dx, 100, "%f.1", 1 / sapp_frame_duration());
}

/* The default draw sprite functions will only be compatible with the basic_atlas shader found in 
 * core shaders for the meantime.
*/
void drawSprite(Texture *s, Vec2 pos, f32 scale, Color color) {
    // Append to the list
    f32 tWidth = s->width;
    f32 tHeight = s->height;

    Sprite sprite = (Sprite){{pos.x, pos.y, scale}, {0, 0, tWidth, tHeight}};
    array_push(s->sprites, sprite);

}

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color);
void drawSpriteEx( Texture *s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color) {
    f32 tWidth = s->width;
    f32 tHeight = s->height;

    Sprite sprite = (Sprite){{pos.x, pos.y, scale}, {tWidth - src.x, tHeight - src.y - size.y, src.x + size.x, src.y + size.y}};
    array_push(s->sprites, sprite);
}

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);

void begin_drawing() {
    sg_begin_pass(&(sg_pass){
        .action = {
            .colors[0] = {
                .load_action = SG_LOADACTION_CLEAR, .clear_value = { 0.25f, 0.5f, 0.7f, 1.0f }
            }
        },
        .swapchain = sglue_swapchain()
    });
}
void end_drawing(){
    const char *keys[256];
    size_t count = hashmap_keys(textures, keys, 256);
    for (size_t i = 0; i < count; i++) {
        Texture *t = hashmap_get(textures, keys[i]);


        Sprite s = t->sprites->data[0];
        //LOG(info, "Sprite: %f %f %f", s.pos.x, s.pos.y, s.pos.z);

        f32 tWidth = t->width;
        f32 tHeight = t->height;
        vs_params_t vs_params = {
            .mvp = Mat4Mul(compute_mvp(_is.cam), Mat4Identity()),
            .atlas_size = {tWidth, tHeight},
        };
        sg_update_buffer(t->bind.vertex_buffers[1], &(sg_range){
            .ptr = t->sprites->data,
            .size = t->sprites->len * sizeof(Sprite),
        });
        sg_apply_pipeline(t->pipe);
        sg_apply_bindings(&t->bind);
        sg_apply_uniforms(UB_vs_params, &SG_RANGE(vs_params));
        sg_draw(0, 6, t->sprites->len);
    }

    sg_end_pass();
    sg_commit();

    for (size_t i = 0; i < count; i++) {
        Texture *t = hashmap_get(textures, keys[i]);
        t->sprites->len = 0;
    }
}
