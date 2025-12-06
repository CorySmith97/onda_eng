
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

Vec2 Vec2Add(Vec2 a, Vec2 b);
Vec2 Vec2Sub(Vec2 a, Vec2 b);
Vec2 Vec2Scale(Vec2 a, f32 scale);
f32  Vec2Dot(Vec2 a, Vec2 b);

Vec3 Vec3Add(Vec3 a, Vec3 b);
Vec3 Vec3Sub(Vec3 a, Vec3 b);
Vec3 Vec3Scale(Vec3 a, f32 scale);
f32  Vec3Dot(Vec3 a, Vec3 b);
Vec3 Vec3Cross(Vec3 a, Vec3 b);

Vec4 Vec4Add(Vec4 a, Vec4 b);
Vec4 Vec4Sub(Vec4 a, Vec4 b);
Vec4 Vec4Scale(Vec4 a, f32 scale);
f32  Vec4Dot(Vec4 a, Vec4 b);
Vec4 Vec4Cross(Vec4 a, Vec4 b);

Mat4 Mat4Mul(Mat4 a, Mat4 b);
Mat4 Mat4Inv(Mat4 a);
Mat4 Mat4Mul_inv(Mat4 a, Mat4 b);
Mat4 Mat4Inv_inv(Mat4 a, Mat4 b);
Mat4 Mat4Transpose(Mat4 a);
Mat4 Mat4Transpose_inv(Mat4 a);
Mat4 Mat4Look_at(Vec3 eye, Vec3 at, Vec3 up);
Mat4 Mat4Ortho( f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);
Mat4 Mat4Identity();


