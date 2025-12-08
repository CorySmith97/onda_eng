@ctype mat4 Mat4

@vs vs_atlas
layout(binding=0) uniform vs_params {
    mat4 mvp;
    vec2 atlas_size;
};

in vec2 position;
in vec2 uv_coords;
in vec3 sprite_pos;
in vec4 sprite_rec;


out vec2 uv;

void main() {
    vec2 pos = position + sprite_pos.xy;
    gl_Position = mvp * vec4(pos * sprite_pos.z, 0.0, 1.0);
    vec2 atlas_uv_min = sprite_rec.xy / atlas_size;
    vec2 atlas_uv_max = (sprite_rec.xy + sprite_rec.zw) / atlas_size;
    uv = atlas_uv_min + uv_coords * (atlas_uv_max - atlas_uv_min);
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

@vs quad_vs
layout(binding=0) uniform quad_vs_params {
    mat4 mvp;
};

in vec2 position;
in vec3 sprite_pos;
in vec4 color;

out vec4 fg_color;

void main() {
    vec2 pos = position + sprite_pos.xy;
    gl_Position = mvp * vec4(pos * sprite_pos.z, 0.0, 1.0);
    fg_color = color;
}
@end

@fs quad_fs
in vec4 fg_color;
out vec4 frag_color;

void main() {
    frag_color = fg_color;
}
@end

@program quad quad_vs quad_fs

