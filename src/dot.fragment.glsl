#include "common.glsl"
STRINGIFY(

    varying vec4 glPos;

    varying vec2 adjusted_offset;
    uniform float ticks;

void main() {
    float d = distance(vec2(glPos), adjusted_offset);
    float t = 1.0 - clamp(d * 10, 0, 1);
    float i = nsin(ticks / 72) * pow(t,  5);
    float b = t > 0 && (t < 0.04 || t > 0.8) ? 1.0 : 0.0;
    b *= 1.0 - nsin(ticks / 72);
    gl_FragColor = vec4(0, i, b, i);
}

) // STRINGIFY
