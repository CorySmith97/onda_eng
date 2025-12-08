// Header Includes
#include "core/core_inc.h"
#include "platform/platform.h"
#include "engine/engine.h"
#include "game/game.h"
#include "profiler/prof.h"

// C Includes
#include "core/core_inc.c"
#include "platform/platform.c"
#include "engine/engine.c"
#include "game/game.c"

int main() {
    app_run(&(PlatformDesc){
            .title = "test 2",
            .backend = BACKEND_SOKOL_NATIVE,
            .init_fn = init,
            .frame_fn = frame,
    });
}

