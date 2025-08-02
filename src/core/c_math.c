//
// Created by Cory Smith on 7/25/25.
//



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




