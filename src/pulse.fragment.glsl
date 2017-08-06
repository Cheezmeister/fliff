#include "common.glsl"
STRINGIFY(

varying vec4 glPos;
varying vec2 adjusted_offset;

uniform float ticks;

void main() {
    float d = distance(vec2(glPos), adjusted_offset);
    float t = 1.0 - clamp(d * 10, 0, 1);
    float b = t > 0 && (t < 0.04 || t > 0.8) ? 1.0 : 0.0;

    vec3 color = vec3(1, 0, 0) * b * nsin(ticks / 144);
    gl_FragColor = vec4(color, 1);
}

) // STRINGIFY

