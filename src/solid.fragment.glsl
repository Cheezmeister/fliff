#include "common.glsl"
STRINGIFY(

    varying vec4 glPos;

    uniform vec3 hsv;

void main() {
    vec3 rgb = hsv2rgb(hsv);
    gl_FragColor = vec4(1, 0, 0, 1);
}

) // STRINGIFY
