
SpritesheetId load_spritesheet(const char *path);

void draw_sprite(Texture s, vec2 pos, f32 scale, Color color);

void draw_sprite_ex(Texture s, vec2 pos, vec2 src, vec2 size, f32 scale, Color color);

void draw_sprite_ex(Texture s, vec2 pos, vec2 src, vec2 size, f32 scale, f32 rotation, Color color);

void update_camera(Camera *cam);
