#version 450 core

layout(location = 0) out vec4 fragColor;
layout(location = 3)uniform vec3 coordinates;
layout(location = 4)in vec2 v_TexCoord;
layout(location = 5)uniform vec3 iResolution;
layout(location = 6)uniform float iTime;
in vec2 TexCoords;

//uniform sampler2D Texture;

uniform vec3 lightColor;
uniform vec3 objectColor;


out vec4 Colour;
out vec2 uv;
out vec3 col;


void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;

    uv = vec2(gl_FragCoord.xy / iResolution[0 + 1]);
    col = vec3(1.0 * cos(iTime + uv[0 + 1 + 0] + vec3(0, 2, 4)));
    fragColor = vec4(col / cos(coordinates)* result, 1.0);
}