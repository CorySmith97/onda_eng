
HashMap *textures;

void engine_init() {
    textures = hashmap_create(sizeof(Texture));
}

// @todo:cs this needs to open file if failed to find in the hashmap.
Texture *load_spritesheet(const char *path) {
    Texture t;
    void *value = (Texture*)hashmap_get(textures, path);
    if (value == NULL) {
        LOG(error, "Failed to load texture: %s", path);
        return NULL;
    }

    return (Texture*)value;
}

void draw_sprite(Texture *s, Vec2 pos, f32 scale, Color color) {
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

    sg_bindings bind;
    bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
        .data = SG_RANGE(verts),
    });
    bind.index_buffer = sg_make_buffer(&(sg_buffer_desc) {
        .usage.index_buffer = true,
        .data = SG_RANGE(indices),
    });

    //sg_pipeline pipe = sg_make_pipeline(&(sg_pipeline_desc){
    //    .layout = {
    //        .attr = {
    //            [ATTR_SimpleTexture_position].format = SG_VERTEXFORMAT_FLOAT2,
    //            [ATTR_SimpleTexture_texturecoord].format = SG_VERTEXFORMAT_FLOAT2,
    //        },
    //    },
    //    .shader = sg_make_shader(SimpleTexture_shader_desc(sg_query_backend())),
    //    .index_type = SG_INDEXTYPE_UINT16,
    //});

    //sg_apply_pipeline(pipe);
    //sg_apply_bindings(&bind);
    //sg_draw(0, 6, 1);
}

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color);

//void draw_sprite_ex(Texture s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);
