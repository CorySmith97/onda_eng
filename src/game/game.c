#include <unistd.h>

typedef enum {
    tile_grass,
    tile_dirt,
    tile_water,
} TileType;

typedef struct Tile {
    TileType type;
} Tile;

static GameState *s;
Tile grid[10][10];

Texture *t;
Texture *m;
Camera2d cam;
f32 delta = 0.75;

void init() {
    t = loadSpritesheet("data/masterspritesheet.png");
    m = loadSpritesheet("data/testmap.png");
    assert(t != NULL);
    cam = (Camera2d){
        .target = {0,0},
        .offset = {0,0},
        .zoom_factor = 0.11f,
        .rotation = 0.0f,
    };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; i < 10; i++) {
        grid[i][j] = (Tile){tile_grass};
        }
    }
}

void frame() {
    ResetProf(); 

    SectionStart("Input");
    if (isKeyPressed(KEY_H)) {
        sleep(1);
    }
    if (isKeyPressed(KEY_M)) {
        delta += 0.005;
    }
    if (isKeyPressed(KEY_N)) {
        delta -= 0.005;
    }
    if (isKeyPressed(KEY_SEMICOLON)) {
        LOG(info, "Global byte count: %llu", global_allocations.total_bytes_allocated);
    }
    if (isKeyPressed(KEY_L)) {
        cam.rotation += 0.005;
    }
    if (isKeyPressed(KEY_K)) {
        cam.rotation -= 0.005;
    }
    if (isKeyPressed(KEY_W)) {
        cam.target.y += 0.01 / cam.zoom_factor;
    }
    if (isKeyPressed(KEY_S)) {
        cam.target.y -= 0.01/ cam.zoom_factor;
    }
    if (isKeyPressed(KEY_D)) {
        cam.target.x += 0.01/ cam.zoom_factor;
    }
    if (isKeyPressed(KEY_A)) {
        cam.target.x -= 0.01/ cam.zoom_factor;
    }
    SectionEnd("Input");

    SectionStart("Update");
    SectionEnd("Update");

    SectionStart("Render");
        
    Vec2 mouse_pos = getMousePos();
    Vec2 world_mouse_pos = screenToWorldSpace2d(cam, mouse_pos);
    LOG(info, "World: %f %f", world_mouse_pos.x, world_mouse_pos.y);

    updateCamera2d(&cam);
    begin_drawing();
    float origin_x = 0.0f;
    float origin_y = 0.0f;
    float tile_w_world = 1.0f; 
    float tile_h_world = 1.0f;

    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (world_mouse_pos.x / sapp_widthf() < i + 1 &&
                world_mouse_pos.x / sapp_widthf() > i && 
                world_mouse_pos.y / sapp_heightf() < j + 1 &&
                world_mouse_pos.y / sapp_heightf() > j) {
                drawSpriteEx(
                    t,
                    (Vec2){ i, j },
                    (Vec2){ 32, 0 }, 
                    (Vec2){ 32, 32 },
                    1.0f,
                    (Color){ 255, 255, 255, 255 }
                );
                continue;
            }
            drawSpriteEx(
                t,
                (Vec2){ i, j },
                (Vec2){ 0, 0 }, 
                (Vec2){ 32, 32 },
                1.0f,
                (Color){ 255, 255, 255, 255 }
            );

        }
    }
    //drawSpriteEx(
    //    m,
    //    (Vec2){world_mouse_pos.x - 0.5, world_mouse_pos.y - 0.5},
    //    (Vec2){ 32, 0 }, 
    //    (Vec2){ 32, 32 },
    //    1.0f,
    //    (Color){ 255, 255, 255, 255 }
    //);

    beginTextDrawing();
    //drawCameraCoords(&cam);
    drawFps();
    endTextDrawing();
    end_drawing();

    SectionEnd("Render");
}

