//
// Created by Cory Smith on 7/25/25.
//
#include <math.h>

//
// =========================
// ===   VEC2 FUNCTIONS  ===
// =========================
//

Vec2 c_vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){ a.x + b.x, a.y + b.y };
}

Vec2 c_vec2_sub(Vec2 a, Vec2 b) {
    return (Vec2){ a.x - b.x, a.y - b.y };
}

Vec2 c_vec2_scale(Vec2 a, f32 s) {
    return (Vec2){ a.x * s, a.y * s };
}

f32 c_vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}


//
// =========================
// ===   VEC3 FUNCTIONS  ===
// =========================
//

Vec3 c_vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3 c_vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

Vec3 c_vec3_scale(Vec3 a, f32 s) {
    return (Vec3){ a.x * s, a.y * s, a.z * s };
}

f32 c_vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 c_vec3_cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vec3 c_vec3_norm(Vec3 a) {
    f32 len = sqrtf(c_vec3_dot(a, a));
    return (len > 0.0f) ? c_vec3_scale(a, 1.0f / len) : a;
}


//
// =========================
// ===   VEC4 FUNCTIONS  ===
// =========================
//

Vec4 c_vec4_add(Vec4 a, Vec4 b) {
    return (Vec4){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

Vec4 c_vec4_sub(Vec4 a, Vec4 b) {
    return (Vec4){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

Vec4 c_vec4_scale(Vec4 a, f32 s) {
    return (Vec4){ a.x * s, a.y * s, a.z * s, a.w * s };
}

f32 c_vec4_dot(Vec4 a, Vec4 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}


//
// =========================
// ===   MAT4 FUNCTIONS  ===
// =========================
//

Mat4 c_mat4_identity() {
    Mat4 m = {0};
    m.m[0][0] = 1.f;
    m.m[1][1] = 1.f;
    m.m[2][2] = 1.f;
    m.m[3][3] = 1.f;
    return m;
}

Mat4 c_mat4_trans(float x, float y, float z) {
    Mat4 m = c_mat4_identity();
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}

Mat4 c_mat4_scale(float x, float y, float z) {
    Mat4 m = {0};
    m.m[0][0] = x;
    m.m[1][1] = y;
    m.m[2][2] = z;
    m.m[3][3] = 1.f;
    return m;
}

Mat4 c_mat4_rot_x(float a) {
    float s = sinf(a), c = cosf(a);
    Mat4 m = c_mat4_identity();
    m.m[1][1] = c;  m.m[2][1] = -s;
    m.m[1][2] = s;  m.m[2][2] = c;
    return m;
}

Mat4 c_mat4_rot_y(float a) {
    float s = sinf(a), c = cosf(a);
    Mat4 m = c_mat4_identity();
    m.m[0][0] = c;  m.m[2][0] = s;
    m.m[0][2] = -s; m.m[2][2] = c;
    return m;
}

Mat4 c_mat4_rot_z(float a) {
    float s = sinf(a), c = cosf(a);
    Mat4 m = c_mat4_identity();
    m.m[0][0] = c;  m.m[1][0] = -s;
    m.m[0][1] = s;  m.m[1][1] = c;
    return m;
}

Mat4 c_mat4_mul(Mat4 a, Mat4 b) {
    Mat4 r = {0};
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            for (int k=0;k<4;k++)
                r.m[i][j] += a.m[i][k] * b.m[k][j];
    return r;
}

Mat4 c_mat4_transpose(Mat4 a) {
    Mat4 r;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            r.m[i][j] = a.m[j][i];
    return r;
}


// --------------------------
// Proper 4×4 matrix inverse
// --------------------------
Mat4 c_mat4_inv(Mat4 m) {
    Mat4 r = {0};
    float inv[16], det;
    float* a = (float*)m.m;

    inv[0] = a[5]  * a[10] * a[15] -
             a[5]  * a[11] * a[14] -
             a[9]  * a[6]  * a[15] +
             a[9]  * a[7]  * a[14] +
             a[13] * a[6]  * a[11] -
             a[13] * a[7]  * a[10];

    inv[4] = -a[4]  * a[10] * a[15] +
             a[4]  * a[11] * a[14] +
             a[8]  * a[6]  * a[15] -
             a[8]  * a[7]  * a[14] -
             a[12] * a[6]  * a[11] +
             a[12] * a[7]  * a[10];

    inv[8] = a[4]  * a[9] * a[15] -
             a[4]  * a[11] * a[13] -
             a[8]  * a[5] * a[15] +
             a[8]  * a[7] * a[13] +
             a[12] * a[5] * a[11] -
             a[12] * a[7] * a[9];

    inv[12] = -a[4]  * a[9] * a[14] +
              a[4]  * a[10] * a[13] +
              a[8]  * a[5] * a[14] -
              a[8]  * a[6] * a[13] -
              a[12] * a[5] * a[10] +
              a[12] * a[6] * a[9];

    inv[1] = -a[1]  * a[10] * a[15] +
             a[1]  * a[11] * a[14] +
             a[9]  * a[2] * a[15] -
             a[9]  * a[3] * a[14] -
             a[13] * a[2] * a[11] +
             a[13] * a[3] * a[10];

    inv[5] = a[0]  * a[10] * a[15] -
             a[0]  * a[11] * a[14] -
             a[8]  * a[2] * a[15] +
             a[8]  * a[3] * a[14] +
             a[12] * a[2] * a[11] -
             a[12] * a[3] * a[10];

    inv[9] = -a[0]  * a[9] * a[15] +
             a[0]  * a[11] * a[13] +
             a[8]  * a[1] * a[15] -
             a[8]  * a[3] * a[13] -
             a[12] * a[1] * a[11] +
             a[12] * a[3] * a[9];

    inv[13] = a[0]  * a[9] * a[14] -
              a[0]  * a[10] * a[13] -
              a[8]  * a[1] * a[14] +
              a[8]  * a[2] * a[13] +
              a[12] * a[1] * a[10] -
              a[12] * a[2] * a[9];

    inv[2] = a[1]  * a[6] * a[15] -
             a[1]  * a[7] * a[14] -
             a[5]  * a[2] * a[15] +
             a[5]  * a[3] * a[14] +
             a[13] * a[2] * a[7] -
             a[13] * a[3] * a[6];

    inv[6] = -a[0]  * a[6] * a[15] +
             a[0]  * a[7] * a[14] +
             a[4]  * a[2] * a[15] -
             a[4]  * a[3] * a[14] -
             a[12] * a[2] * a[7] +
             a[12] * a[3] * a[6];

    inv[10] = a[0]  * a[5] * a[15] -
              a[0]  * a[7] * a[13] -
              a[4]  * a[1] * a[15] +
              a[4]  * a[3] * a[13] +
              a[12] * a[1] * a[7] -
              a[12] * a[3] * a[5];

    inv[14] = -a[0]  * a[5] * a[14] +
              a[0]  * a[6] * a[13] +
              a[4]  * a[1] * a[14] -
              a[4]  * a[2] * a[13] -
              a[12] * a[1] * a[6] +
              a[12] * a[2] * a[5];

    inv[3] = -a[1] * a[6] * a[11] +
              a[1] * a[7] * a[10] +
              a[5] * a[2] * a[11] -
              a[5] * a[3] * a[10] -
              a[9] * a[2] * a[7] +
              a[9] * a[3] * a[6];

    inv[7] = a[0] * a[6] * a[11] -
             a[0] * a[7] * a[10] -
             a[4] * a[2] * a[11] +
             a[4] * a[3] * a[10] +
             a[8] * a[2] * a[7] -
             a[8] * a[3] * a[6];

    inv[11] = -a[0] * a[5] * a[11] +
               a[0] * a[7] * a[9] +
               a[4] * a[1] * a[11] -
               a[4] * a[3] * a[9] -
               a[8] * a[1] * a[7] +
               a[8] * a[3] * a[5];

    inv[15] = a[0] * a[5] * a[10] -
              a[0] * a[6] * a[9] -
              a[4] * a[1] * a[10] +
              a[4] * a[2] * a[9] +
              a[8] * a[1] * a[6] -
              a[8] * a[2] * a[5];

    det = a[0] * inv[0] + a[1] * inv[4] + a[2] * inv[8] + a[3] * inv[12];
    det = 1.f / det;

    for (int i=0; i<16; i++)
        ((float*)r.m)[i] = inv[i] * det;

    return r;
}


//
// =========================
// ===   LOOK AT MATRIX   ===
// =========================
//

Mat4 c_mat4_look_at(Vec3 eye, Vec3 at, Vec3 up) {
    Vec3 f = c_vec3_norm(c_vec3_sub(at, eye));     // Forward
    Vec3 r = c_vec3_norm(c_vec3_cross(f, up));     // Right
    Vec3 u = c_vec3_cross(r, f);                   // Up

    Mat4 m = c_mat4_identity();

    m.m[0][0] = r.x;  m.m[1][0] = r.y;  m.m[2][0] = r.z;
    m.m[0][1] = u.x;  m.m[1][1] = u.y;  m.m[2][1] = u.z;
    m.m[0][2] = -f.x; m.m[1][2] = -f.y; m.m[2][2] = -f.z;

    m.m[3][0] = -c_vec3_dot(r, eye);
    m.m[3][1] = -c_vec3_dot(u, eye);
    m.m[3][2] =  c_vec3_dot(f, eye);

    return m;
}


//
// ================================
// ===   ORTHOGRAPHIC PROJECTION ===
// ================================
//

Mat4 c_mat4_ortho(
    f32 left, f32 right,
    f32 bottom, f32 top,
    f32 near, f32 far) {
    Mat4 m = {0};

    m.m[0][0] = 2.f / (right - left);
    m.m[1][1] = 2.f / (top - bottom);
    m.m[2][2] = -2.f / (far - near);

    m.m[3][0] = -(right + left) / (right - left);
    m.m[3][1] = -(top + bottom) / (top - bottom);
    m.m[3][2] = (far + near) / (far - near);
    m.m[3][3] = 1.f;

    return m;
}

