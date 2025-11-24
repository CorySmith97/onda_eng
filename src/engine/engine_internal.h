#pragma once

/*
This is the private header file for the runtime.
 */

// State from the game dll.
void *GameState;

// Game defined data.
typedef struct Plugin {
    void* (*game_init_fn)(void);
    void (*game_tick_fn)(void*);
    void (*game_input_fn)(void*);
    void (*game_deinit_fn)(void*);
} Plugin;
