#version 450 core

layout(location = 0) out vec4 fragColor;


in vec2 v_TexCoord;
in vec3 OutNormals;
in vec3 CurrentPosition;

out vec4 Colour;
out vec2 uv;
out vec3 col;

uniform vec3 coordinates;
uniform float iTime;
uniform vec3 iResolution;
//uniform sampler2D Texture;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 LightPos;



void main()
{
    vec3 OutNormals = normalize(OutNormals);
    vec3 lightDirection = normalize(LightPos - CurrentPosition);
    float diffuse = max(dot(OutNormals, lightDirection), 0.0);
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = ambient * objectColor;
    uv = vec2(gl_FragCoord.xy / iResolution.xy);
    col = vec3(1.0 * cos(iTime + uv.xyx+ vec3(0, 2, 4)));
    float speclight = 0.5;
    vec3 viewDirection = normalize(coordinates - CurrentPosition);
    vec3 reflectionDirection = reflect(-lightDirection, OutNormals);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8);
    float specular = specAmount * speclight;

    fragColor = vec4(col / cos(coordinates)* (diffuse + result + specular), 1.0);

}