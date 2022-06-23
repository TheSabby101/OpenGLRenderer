#version 330 core

layout(location = 0)out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D Texture;
uniform vec4 u_colour;


void main() {
vec4 TexColor = texture(Texture, v_TexCoord);
color = TexColor;
}