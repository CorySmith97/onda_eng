// Header Includes
#include "core/core.h"
#include "platform/platform.h"

// C Includes
#include "core/c_main.c"
#include "platform/platform.c"

int main() {
    app_run(&(PlatformDesc){
            .title = "test 2",
            .backend = BACKEND_SOKOL_NATIVE,
    });
}

