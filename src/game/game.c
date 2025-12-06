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
        .zoom_factor = 0.01,
    };
    for (int i = 0; i < 10; i++) {
        for (int j = 0; i < 10; i++) {
        grid[i][j] = (Tile){tile_grass};
        }
    }
}

void frame() {
    if (isKeyPressed(KEY_M)) {
        delta += 0.005;
    }
    if (isKeyPressed(KEY_N)) {
        delta -= 0.005;
    }
    if (isKeyPressed(KEY_SEMICOLON)) {
        LOG(info, "Global byte count: %u", global_allocations.total_bytes_allocated);
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
    Vec2 mouse_pos = getMousePos();

    // LOG(info, "%f, %f", mouse_pos.x, mouse_pos.y);
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

    drawSprite(m, mouseToWorldPosition(cam, mouse_pos), 1.0, (Color){0});

    beginTextDrawing();
    drawCameraCoords(&cam);
    drawFps();
    endTextDrawing();
    end_drawing();
}

