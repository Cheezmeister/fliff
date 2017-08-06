#include "common.glsl"
STRINGIFY(

varying vec4 glPos;

uniform float metervalue;

void main() {
    vec3 level1 = vec3(0, 255, 0);
    vec3 level2 = vec3(0, 255, 255);

    vec3 backcolor = vec3(0, 0, 0);
    vec3 color = level1;

    if (metervalue > 100) color = level2;
    if (metervalue > 100) backcolor = level1;

    float fillvalue = mod(metervalue, 100) / 100.0;
    if (abs(glPos.x) > fillvalue)
    {
        gl_FragColor = vec4(backcolor, 1);
    }
    else
    {
        gl_FragColor = vec4(color, 1);
    }
}

) // STRINGIFY
