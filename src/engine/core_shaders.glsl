@ctype mat4 Mat4

@vs vs_atlas
layout(binding=0) uniform vs_params {
    mat4 mvp;
    vec2 atlas_size;
};

in vec2 position;
in vec2 uv_coords;

in vec4 sprite_rec;
in vec4 screen_rect;


out vec2 uv;

void main() {
    gl_Position =  mvp * vec4((position), 0.0, 1.0);
    uv = uv_coords;
}
@end

@fs fs_atlas
layout(binding=0) uniform texture2D tex2d;
layout(binding=0) uniform sampler smp;
in vec2 uv;

out vec4 frag_color;

void main() {
     frag_color = texture(sampler2D(tex2d, smp), uv);
}
@end

@program basic_atlas vs_atlas fs_atlas

