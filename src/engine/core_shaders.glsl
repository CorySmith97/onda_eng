@ctype mat4 Mat4

@vs vs_atlas
layout(binding=0) uniform vs_params {
    mat4 mvp;
    vec2 atlas_size;
    vec4 sprite_rec;
};

in vec2 position;
in vec2 uv_coords;


out vec2 uv;

void main() {
    gl_Position =  mvp * vec4((position), 0.0, 1.0);
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

