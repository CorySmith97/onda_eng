//
// Created by Cory Smith on 7/27/25.
//

#include "render.h"
#define OPENGL

#if defined(VULKAN)
#   include "r_vk_init.c"
#elif defined(OPENGL)
#   include "r_gl_init.c"
#else
#   error "need a backend"
#endif
