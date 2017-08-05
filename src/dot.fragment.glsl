#include "common.glsl"
STRINGIFY(

    /* attribute vec4 inPos; */
    varying vec4 glPos;

    varying vec2 adjusted_offset;

void main() {
    float d = distance(vec2(glPos), adjusted_offset);
    float t = 1.0 - clamp(d * 10, 0, 1);
    float i = pow(t, 5);
    float b = t > 0 && (t < 0.04 || t > 0.8) ? 1.0 : 0.0;
    gl_FragColor = vec4(0, i, b, i);
}

) // STRINGIFY
