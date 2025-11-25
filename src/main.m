#include <stdio.h>

// Header Includes
#include "core/core_inc.h"
#include "platform/platform.h"

// C Includes
#include "core/c_main.c"
#include "platform/platform.c"

void frame() {
    if (isKeyPressed(32)) {
        printf("Key pressed. \n");
    }
}

int main() {
    app_run(&(PlatformDesc){
            .title = "test 2",
            .backend = BACKEND_SOKOL_NATIVE,
            .frame_fn = frame,
    });
}

