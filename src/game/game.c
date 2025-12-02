

static GameState *s;

Texture *t;
Camera cam;

void init() {
    t = load_spritesheet("data/testmap.png");
    cam = (Camera){
        .pos = {0, 0, 0},
        .up = {0, 1, 0},
        .target = {0, 0, 0},
        .fov = 45,
        .type = CAMERA_2D,
        .zoom_factor = 0.25,
    };
}

void frame() {
    if (isKeyPressed(KEY_W)) {
        cam.pos.y += 0.01;
    }
    if (isKeyPressed(KEY_S)) {
        cam.pos.y -= 0.01;
    }
    if (isKeyPressed(KEY_D)) {
        cam.pos.x += 0.01;
    }
    if (isKeyPressed(KEY_A)) {
        cam.pos.x -= 0.01;
    }
    update_camera(&cam);
    begin_drawing();
    drawSpriteEx(t, (Vec2){0, 0}, (Vec2){400, 400}, (Vec2){300, 300}, 0.1, (Color){255, 255, 255, 255});

    beginTextDrawing();
    drawFps();
    endTextDrawing();
    end_drawing();
}

