//
// Created by Cory Smith on 7/27/25.
//

#include "render.h"

#ifdef VULKAN
#include "r_vk_init.c"
#elif OPENGL
#include "r_gl_init.c"
#endif
