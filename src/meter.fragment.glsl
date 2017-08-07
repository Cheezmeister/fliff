#include "common.glsl"
STRINGIFY(

varying vec4 glPos;

uniform float metervalue;
uniform float ticks;

void main() {
    vec3 colors[10];
    colors[0] = vec3(0, 0, 0);
    colors[1] = vec3(0.3, 1, 0.5);
    colors[2] = vec3(0.5, 1, 0.5);
    colors[3] = vec3(0.7, 1, 0.5);
    colors[4] = vec3(0.9, 1, 0.5);
    colors[5] = vec3(0.2, 1, 0.8);
    colors[6] = vec3(0.4, 1, 0.8);
    colors[7] = vec3(0.6, 1, 0.8);
    colors[8] = vec3(0.8, 1, 0.8);
    colors[9] = vec3(0.9, 1, 1.0);

    int f = int(floor(metervalue / 100));

    vec3 backcolor = hsv2rgb(colors[f]);
    vec3 color = hsv2rgb(colors[f+1]);

    float fillvalue = mod(metervalue, 100) / 100.0;
    if (abs(glPos.x) > fillvalue)
    {
        gl_FragColor = vec4(backcolor, 1) * (0.5 + abs(glPos.y - 0.9) * 5 * beat(ticks * 8));
    }
    else
    {
        gl_FragColor = vec4(color * (1 - beat(ticks) / 1.2 * abs(glPos.x) ), 1);
    }
}

) // STRINGIFY
