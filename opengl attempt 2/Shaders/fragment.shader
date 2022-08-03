#version 450 core
layout(location = 0)out vec4 fragColor;
layout(location = 3)in vec2 v_TexCoord;
uniform vec4 u_colour;
uniform sampler2D Texture;

void main() {
	fragColor = texture(Texture, v_TexCoord) * u_colour;
}