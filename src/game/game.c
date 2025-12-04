typedef enum {
    tile_grass,
    tile_dirt,
    tile_water,
} TileType;

typedef struct Tile {
    TileType type;
} Tile;

static GameState *s;
Tile grid[100];

Texture *t;
Camera cam;

void init() {
    t = load_spritesheet("data/masterspritesheet.png");
    assert(t != NULL);
    cam = (Camera){
        .pos = {0, 0, 0},
        .up = {0, 1, 0},
        .target = {0, 0, 0},
        .fov = 45,
        .type = CAMERA_2D,
        .zoom_factor = 0.25,
    };
    for (int i = 0; i < 100; i++) {
        grid[i] = (Tile){tile_grass};
    }
}

void frame() {
    if (isKeyPressed(KEY_L)) {
        cam.zoom_factor += 0.05;
    }
    if (isKeyPressed(KEY_K)) {
        cam.zoom_factor += 0.05;
    }
    if (isKeyPressed(KEY_W)) {
        cam.pos.y += 0.01 / cam.zoom_factor;
    }
    if (isKeyPressed(KEY_S)) {
        cam.pos.y -= 0.01/ cam.zoom_factor;
    }
    if (isKeyPressed(KEY_D)) {
        cam.pos.x += 0.01/ cam.zoom_factor;
    }
    if (isKeyPressed(KEY_A)) {
        cam.pos.x -= 0.01/ cam.zoom_factor;
    }
    update_camera(&cam);
    begin_drawing();
    //drawSprite(t, (Vec2){10, 10}, 0.1, (Color){255, 255, 255, 255});
    for (int i = 0; i < 100; i++) {
        drawSpriteEx(t, (Vec2){i + 32, 0}, (Vec2){0, 0}, (Vec2){32, 32}, 10, (Color){255, 255, 255, 255});
    }

    beginTextDrawing();
    drawFps();
    endTextDrawing();
    end_drawing();
}

