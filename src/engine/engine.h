#ifndef ENGINE_H
#define ENGINE_H
/*
Engine runtime API
*/

// Types
typedef struct Sprite {
    sg_image handle;
} Sprite;

typedef struct Camera2D {
    Vec3 pos;
    Vec3 up;
    Vec3 target;
} Camera2D;

// Functions

// Drawing
void drawSprite(Sprite, Vec2, f32, Color);
void drawSpriteEx(Sprite, Vec2, f32, Color);
void drawSpritePro(Sprite);

#endif  // ENGINE_H
