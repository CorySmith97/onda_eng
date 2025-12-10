//
// Created by Cory Smith on 7/25/25.
//
#include <math.h>

Vec2 Vec2Add(Vec2 a, Vec2 b) {
    return (Vec2){ a.x + b.x, a.y + b.y };
}

Vec2 Vec2Sub(Vec2 a, Vec2 b) {
    return (Vec2){ a.x - b.x, a.y - b.y };
}

Vec2 Vec2Scale(Vec2 a, f32 s) {
    return (Vec2){ a.x * s, a.y * s };
}

f32 Vec2Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}


Vec3 Vec3Add(Vec3 a, Vec3 b) {
    return (Vec3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

Vec3 Vec3Sub(Vec3 a, Vec3 b) {
    return (Vec3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

Vec3 Vec3Scale(Vec3 a, f32 s) {
    return (Vec3){ a.x * s, a.y * s, a.z * s };
}

f32 Vec3Dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3Cross(Vec3 a, Vec3 b) {
    return (Vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vec3 Vec3Norm(Vec3 a) {
    f32 len = sqrtf(Vec3Dot(a, a));
    return (len > 0.0f) ? Vec3Scale(a, 1.0f / len) : a;
}

Vec3 Vec3Transform(Vec3 a, Mat4 mat) {
    Vec3 result = { 0 };

    f32 x = a.x;
    f32 y = a.y;
    f32 z = a.z;

    result.x = mat.m[0][0]*x + mat.m[0][1]*y + mat.m[0][2]*z + mat.m[0][3];
    result.y = mat.m[1][0]*x + mat.m[1][1]*y + mat.m[1][2]*z + mat.m[1][3];
    result.z = mat.m[2][0]*x + mat.m[2][1]*y + mat.m[2][2]*z + mat.m[2][3];

    return result;
}

Vec4 Vec4Add(Vec4 a, Vec4 b) {
    return (Vec4){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

Vec4 Vec4Sub(Vec4 a, Vec4 b) {
    return (Vec4){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

Vec4 Vec4Scale(Vec4 a, f32 s) {
    return (Vec4){ a.x * s, a.y * s, a.z * s, a.w * s };
}

f32 Vec4Dot(Vec4 a, Vec4 b) {
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

Mat4 Mat4Identity() {
    Mat4 m = {0};
    m.m[0][0] = 1.f;
    m.m[1][1] = 1.f;
    m.m[2][2] = 1.f;
    m.m[3][3] = 1.f;
    return m;
}

Mat4 Mat4Trans(f32 x, f32 y, f32 z) {
    Mat4 m = Mat4Identity();
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}

Mat4 Mat4Scale(float x, float y, float z) {
    Mat4 m = {0};
    m.m[0][0] = x;
    m.m[1][1] = y;
    m.m[2][2] = z;
    m.m[3][3] = 1.f;
    return m;
}

Mat4 Mat4RotX(float a) {
    float s = sinf(a), c = cosf(a);
    Mat4 m = Mat4Identity();
    m.m[1][1] = c;  m.m[2][1] = -s;
    m.m[1][2] = s;  m.m[2][2] = c;
    return m;
}

Mat4 Mat4RotY(float a) {
    float s = sinf(a), c = cosf(a);
    Mat4 m = Mat4Identity();
    m.m[0][0] = c;  m.m[2][0] = s;
    m.m[0][2] = -s; m.m[2][2] = c;
    return m;
}

Mat4 Mat4RotZ(float a) {
    float s = sinf(a), c = cosf(a);
    Mat4 m = Mat4Identity();
    m.m[0][0] = c;  m.m[1][0] = -s;
    m.m[0][1] = s;  m.m[1][1] = c;
    return m;
}

Mat4 Mat4Mul(Mat4 a, Mat4 b) {
    Mat4 r = {0};
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            for (int k=0;k<4;k++)
                r.m[i][j] += a.m[i][k] * b.m[k][j];
    return r;
}

Mat4 Mat4Transpose(Mat4 a) {
    Mat4 r;
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            r.m[i][j] = a.m[j][i];
    return r;
}

Mat4 Mat4Inv(Mat4 mat) {
    // ADJUSTED FROM RAYLIB
    Mat4 result = {0};
    f32 a00 = mat.m[0][0], a01 = mat.m[0][1], a02 = mat.m[0][2], a03 = mat.m[0][3];
    f32 a10 = mat.m[0][1], a11 = mat.m[1][1], a12 = mat.m[1][2], a13 = mat.m[1][3];
    f32 a20 = mat.m[0][2], a21 = mat.m[1][2], a22 = mat.m[2][2], a23 = mat.m[2][3];
    f32 a30 = mat.m[0][3], a31 = mat.m[1][3], a32 = mat.m[3][2], a33 = mat.m[3][3];
    
    f32 b00 = a00*a11 - a01*a10;
    f32 b01 = a00*a12 - a02*a10;
    f32 b02 = a00*a13 - a03*a10;
    f32 b03 = a01*a12 - a02*a11;
    f32 b04 = a01*a13 - a03*a11;
    f32 b05 = a02*a13 - a03*a12;
    f32 b06 = a20*a31 - a21*a30;
    f32 b07 = a20*a32 - a22*a30;
    f32 b08 = a20*a33 - a23*a30;
    f32 b09 = a21*a32 - a22*a31;
    f32 b10 = a21*a33 - a23*a31;
    f32 b11 = a22*a33 - a23*a32;

    // Calculate the invert determinant (inlined to avoid double-caching)
    float invDet = 1.0f/(b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);

    result.m[0][0] = (a11*b11 - a12*b10 + a13*b09)*invDet;
    result.m[0][1]= (-a01*b11 + a02*b10 - a03*b09)*invDet;
    result.m[0][2]= (a31*b05 - a32*b04 + a33*b03)*invDet;
    result.m[0][3]= (-a21*b05 + a22*b04 - a23*b03)*invDet;
    result.m[1][0]= (-a10*b11 + a12*b08 - a13*b07)*invDet;
    result.m[1][1]= (a00*b11 - a02*b08 + a03*b07)*invDet;
    result.m[1][2]= (-a30*b05 + a32*b02 - a33*b01)*invDet;
    result.m[1][3]= (a20*b05 - a22*b02 + a23*b01)*invDet;
    result.m[2][0]= (a10*b10 - a11*b08 + a13*b06)*invDet;
    result.m[2][1]= (-a00*b10 + a01*b08 - a03*b06)*invDet;
    result.m[2][2] = (a30*b04 - a31*b02 + a33*b00)*invDet;
    result.m[2][3] = (-a20*b04 + a21*b02 - a23*b00)*invDet;
    result.m[3][0] = (-a10*b09 + a11*b07 - a12*b06)*invDet;
    result.m[3][1] = (a00*b09 - a01*b07 + a02*b06)*invDet;
    result.m[3][2] = (-a30*b03 + a31*b01 - a32*b00)*invDet;
    result.m[3][3] = (a20*b03 - a21*b01 + a22*b00)*invDet;
    return result;
}


//
// =========================
// ===   LOOK AT MATRIX   ===
// =========================
//

Mat4 Mat4LookAt(Vec3 eye, Vec3 at, Vec3 up) {
    Vec3 f = Vec3Norm(Vec3Sub(at, eye));     // Forward
    Vec3 r = Vec3Norm(Vec3Cross(f, up));     // Right
    Vec3 u = Vec3Cross(r, f);                   // Up

    Mat4 m = Mat4Identity();

    m.m[0][0] = r.x;  m.m[1][0] = r.y;  m.m[2][0] = r.z;
    m.m[0][1] = u.x;  m.m[1][1] = u.y;  m.m[2][1] = u.z;
    m.m[0][2] = -f.x; m.m[1][2] = -f.y; m.m[2][2] = -f.z;

    m.m[3][0] = -Vec3Dot(r, eye);
    m.m[3][1] = -Vec3Dot(u, eye);
    m.m[3][2] =  Vec3Dot(f, eye);

    return m;
}


//
// ================================
// ===   ORTHOGRAPHIC PROJECTION ===
// ================================
//

Mat4 Mat4Ortho(
    f32 left, f32 right,
    f32 bottom, f32 top,
    f32 near, f32 far) {
    Mat4 m = {0};

    m.m[0][0] = 2.f / (right - left);
    m.m[1][1] = 2.f / (top - bottom);
    m.m[2][2] = -2.f / (far - near);

    m.m[3][0] = -(right + left) / (right - left);
    m.m[3][1] = -(top + bottom) / (top - bottom);
    m.m[3][2] = -(far + near) / (far - near);
    m.m[3][3] = 1.f;

    return m;
}

