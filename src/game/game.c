

static GameState *s;

Texture *t;
void init() {
    t = load_spritesheet("data/testmap.png");
    LOG(info, "Texture %p", t);
}

void frame() {
    if (isKeyPressed(32)) {
        printf("Key pressed. \n");
    }
    begin_drawing();
    draw_sprite(t, (Vec2){1, 1}, 1, (Color){255, 255, 255, 255});
    end_drawing();
}

