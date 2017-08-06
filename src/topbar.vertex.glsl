/* This file is (ab)used by the C preprocessor
   to embed shaders in gfx.cpp at compile time. */
#include "common.glsl"
STRINGIFY(

    attribute vec4 inPos;
    varying vec4 glPos;

void main() {
    // hax
    vec4 pos = inPos;
    pos.y += 1;
    pos.x *= 10;

    gl_Position = glPos = pos;
}

)
#undef STRINGIFY
