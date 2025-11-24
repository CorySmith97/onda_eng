#ifndef ENGINE_H
#define ENGINE_H
/*
Engine runtime API
*/
#include "../core/core.h"

// Types
typedef struct Sprite {
} Sprite;

typedef struct Camera2D {
    Vec3 pos;
    Vec3 up;
    Vec3 target;
} Camera2D;

typedef enum KeyboardKeys {
};

typedef enum MouseButton {
};

// Functions

// Drawing
void drawSprite(Sprite);
void drawSpriteEx(Sprite);
void drawSpritePro(Sprite);

#endif  // ENGINE_H
