#include "common.glsl"
STRINGIFY(

varying vec4 glPos;

uniform float ticks;
uniform vec3 hsv;

void main() {
    vec3 rgb = hsv2rgb(hsv);
    if (0.8 < beat(ticks * 4))
    {
      rgb = vec3(1) - rgb;
    }
    gl_FragColor = vec4(rgb, 1);
}

) // STRINGIFY
