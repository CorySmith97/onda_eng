
// MATH

typedef union Vec2 {
    struct {f32 x, y;};
    f32 v[2];
} Vec2;
typedef union Vec3 {
    struct {f32 x, y, z;};
    f32 v[3];
} Vec3;
typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;
typedef struct Mat4 {
    f32 m[4][4];
} Mat4;

extern Vec2 c_vec2_add(Vec2 a, Vec2 b);
extern Vec2 c_vec2_sub(Vec2 a, Vec2 b);
extern Vec2 c_vec2_scale(Vec2 a, f32 scale);
extern f32  c_vec2_dot(Vec2 a, Vec2 b);

extern Vec3 c_vec3_add(Vec3 a, Vec3 b);
extern Vec3 c_vec3_sub(Vec3 a, Vec3 b);
extern Vec3 c_vec3_scale(Vec3 a, f32 scale);
extern f32  c_vec3_dot(Vec3 a, Vec3 b);
extern Vec3 c_vec3_cross(Vec3 a, Vec3 b);

extern Vec4 c_vec4_add(Vec4 a, Vec4 b);
extern Vec4 c_vec4_sub(Vec4 a, Vec4 b);
extern Vec4 c_vec4_scale(Vec4 a, f32 scale);
extern f32  c_vec4_dot(Vec4 a, Vec4 b);
extern Vec4 c_vec4_cross(Vec4 a, Vec4 b);

extern Mat4 c_mat4_mul(Mat4 a, Mat4 b);
extern Mat4 c_mat4_inv(Mat4 a);
extern Mat4 c_mat4_mul_inv(Mat4 a, Mat4 b);
extern Mat4 c_mat4_inv_inv(Mat4 a, Mat4 b);
extern Mat4 c_mat4_transpose(Mat4 a);
extern Mat4 c_mat4_transpose_inv(Mat4 a);
extern Mat4 c_mat4_look_at(Vec3 eye, Vec3 at, Vec3 up);
extern Mat4 c_mat4_ortho(Vec3 min, Vec3 max);
extern Mat4 c_mat4_identity();


