#define NOB_STRIP_PREFIX
#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    Cmd cmd = {0};
    cmd_append(&cmd, "sh", "shader.sh");
    if (!cmd_run_sync(cmd)) return 1;

    cmd.count = 0;
    cmd_append(&cmd, "clang", "-o", "bin/game", "src/main.m", "-g");
    cmd_append(&cmd, "-I./src/thirdparty");
    cmd_append(&cmd, "-framework", "Cocoa");
    cmd_append(&cmd, "-framework", "Metal");
    cmd_append(&cmd, "-framework", "MetalKit");
    cmd_append(&cmd, "-framework", "Foundation");
    cmd_append(&cmd, "-framework", "QuartzCore");
    if (!cmd_run_sync(cmd)) return 1;

    cmd.count = 0;
    cmd_append(&cmd, "./bin/game");
    if (!cmd_run_sync(cmd)) return 1;


    return 0;
}
