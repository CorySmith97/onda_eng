#!/bin/sh

set -xe

./data/sokol-shdc -i src/engine/core_shaders.glsl -o src/engine/core_shaders.h -l glsl430:hlsl5:metal_macos
