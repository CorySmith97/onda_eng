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
Camera cam;
f32 delta = 0.75;

void init() {
    t = loadSpritesheet("data/masterspritesheet.png");
    m = loadSpritesheet("data/testmap.png");
    assert(t != NULL);
    cam = (Camera){
        .pos = {0, 0, 0},
        .up = {0, 1, 0},
        .target = {0, 0, 0},
        .fov = 45,
        .type = CAMERA_2D,
        .zoom_factor = 0.02,
    };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; i < 10; i++) {
        grid[i][j] = (Tile){tile_grass};
        }
    }
}

bool isPointInIsoTile(Vec2 point, f32 tile_x, f32 tile_y, f32 tile_width, f32 tile_height) {
    // Transform point relative to tile position
    f32 px = point.x - tile_x;
    f32 py = point.y - tile_y;
    
    // Check if point is inside the diamond shape
    f32 half_width = tile_width / 2.0f;
    f32 half_height = tile_height / 2.0f;
    
    return (fabsf(px) / half_width + fabsf(py) / half_height) <= 1.0f;
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
        cam.zoom_factor += 0.005;
    }
    if (isKeyPressed(KEY_K)) {
        cam.zoom_factor -= 0.005;
    }
    if (isKeyPressed(KEY_W)) {
        cam.pos.y -= 0.001 / cam.zoom_factor;
    }
    if (isKeyPressed(KEY_S)) {
        cam.pos.y += 0.001/ cam.zoom_factor;
    }
    if (isKeyPressed(KEY_D)) {
        cam.pos.x -= 0.001/ cam.zoom_factor;
    }
    if (isKeyPressed(KEY_A)) {
        cam.pos.x += 0.001/ cam.zoom_factor;
    }
    SectionEnd("Input");

    SectionStart("Update");
    SectionEnd("Update");

    SectionStart("Render");
        
    Vec2 mouse_pos = getMousePos();
    Vec2 world_mouse_pos = mouseToWorldPosition(cam, mouse_pos);

    update_camera(&cam);
    begin_drawing();
    float origin_x = 0.0f;
    float origin_y = 0.0f;
    float tile_w_world = 1.0f; 
    float tile_h_world = 1.0f;

    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            float sx = origin_x + (float)(i - j) * (tile_w_world * 0.5f);
            float sy = origin_y + (float)(i + j) * (tile_h_world * 0.5f - delta);
            if (isPointInIsoTile(world_mouse_pos, sx + 0.5, sy + 0.5, 1, 1)) {
                drawSpriteEx(
                    t,
                    (Vec2){ sx, sy },
                    (Vec2){ 32, 0 }, 
                    (Vec2){ 32, 32 },
                    1.0f,
                    (Color){ 255, 255, 255, 255 }
                );
                continue;
            }
            drawSpriteEx(
                t,
                (Vec2){ sx, sy },
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
    drawCameraCoords(&cam);
    drawFps();
    endTextDrawing();
    end_drawing();

    SectionEnd("Render");

    for (int i = 0; i < profiler.sections.len; i++) {
        Section s = profiler.sections.data[i];
        LOG(info, "%s: %lluns (%.3fms)", s.name.data, s.delta_ns, s.delta_ns / 1000000.0);
    }
}

