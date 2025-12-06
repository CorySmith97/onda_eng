#ifdef SOKOL
#   define SOKOL_IMPL
#   define SOKOL_METAL
#   define SOKOL_NO_ENTRY
#   include <sokol_app.h>
#   include <sokol_gfx.h>
#   include <sokol_glue.h>
#   include <sokol_log.h>
#   include <sokol_gl.h>
#   define FONTSTASH_IMPLEMENTATION
#   include <fontstash.h>
#   define SOKOL_FONTSTASH_IMPL
#   include <sokol_fontstash.h>
#endif
