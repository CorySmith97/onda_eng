//
// Created by Cory Smith on 7/25/25.
//

// Vec2

typedef struct Vec2 {
    f32 x, y;
} Vec2;

Vec2 c_vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){a.x + b.x, a.y + b.y};
}

Vec2 c_vec2_sub(Vec2 a, Vec2 b) {
    return (Vec2){a.x - b.x, a.y - b.y};
}

Vec2 c_vec2_scale(Vec2 a, f32 b) {
    return (Vec2){a.x * b, a.y * b};
}

f32 c_vec2_dot(Vec2 a, Vec2 b) {
    return (a.x * b.x + a.y * b.y);
}

// Vec3

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

// Vec4

struct Vec4 {
    f32 x, y, z, w;
};

// Mat4

struct Mat4 {
    f32 m[16];
};


