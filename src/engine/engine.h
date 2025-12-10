#ifndef ENGINE_H
#define ENGINE_H
/*
Engine runtime API
*/
#define SOKOL_METAL
#include <sokol_gfx.h>
#include <sokol_app.h>
#include <sokol_glue.h>
#include <sokol_log.h>

typedef enum {
    CAMERA_ORTHOGRAPHIC,
    CAMERA_PERSPECTIVE,
    CAMERA_2D,
} CameraTypes;

typedef struct Camera2d {
    Vec2 target;
    Vec2 offset;
    f32 rotation;
    f32 zoom_factor;
} Camera2d;

typedef struct Camera {
    Vec3 pos;
    Vec3 target;
    Vec3 up;
    f32 fov;
    f32 zoom_factor;
    CameraTypes type;
} Camera;

typedef struct RectangleI32 {
    i32 x;
    i32 y;
    i32 width;
    i32 height;
} RectangleI32;

typedef struct RectangleF32 {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
} RectangleF32;

typedef struct Shader {
	i32 id;
} Shader;

typedef struct OndaFont {
    char *name;
    i32 id;
} OndaFont;

typedef struct ArrayOndaFonts {
    ArrayHeader _;
    OndaFont *data;
} ArrayOndaFonts;

typedef struct Sprite {
    Vec3 pos;
    Vec4 rec;
    //Vec4 color;
} Sprite;

typedef struct ArraySprite {
    u32 len;
    u32 capacity;
    Sprite *data;
} ArraySprite;

typedef struct Texture {
    i32 width, height;
    sg_bindings bind;
    sg_pipeline pipe;
    sg_image img;
    sg_view view;
    sg_sampler smp;
    ArraySprite *sprites;
} Texture;

typedef struct Mesh {
} Mesh;

typedef struct Model {
} Model;

typedef struct Color {
    u8 r, g, b, a;
} Color;

//
// FUNCTION PROTO
//

/** @brief this initializes the internal systems of the engine runtime.
 */
void engineInit(void);

/** @brief Convert the mouse position to a world space position based on the camera type
 */
Vec2 mouseToWorldSpace(Camera cam, Vec2 mouse_pos);

/** @brief Load a spritesheet with the default atlas shader provided in the basic shaders file.
 */
Texture *loadSpritesheet(const char *path);

/** @brief Drawing function for a single sprite. The sprite for this is the entire image.
 */
void drawSprite(Texture *s, Vec2 pos, f32 scale, Color color);

/** @brief Drawing function for a single sprite from a spritesheet.
 *      src is the starting position of the sprite. size is the 
 *      width/height of the sprite as found on the spritesheet.
 */
void drawSpriteEx(Texture *s, Vec2 pos, Vec2 src, Vec2 size, f32 scale, Color color);

/** @brief Get a camera matrix (View matrix) from a 2d camera
  */
Mat4 getCamera2dMatrix(Camera2d cam);

/**
  */
void updateCamera(Camera *cam);

/**
  */
Mat4 getCameraMatrix(Camera cam);

/**
  */
void beginTextDrawing(void);

#endif  // ENGINE_H
