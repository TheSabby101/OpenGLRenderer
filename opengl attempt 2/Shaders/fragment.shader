#version 430 core

layout(location = 4)in vec2 v_TexCoord;
out vec4 Colour;
uniform vec4 u_colour;


uniform sampler2D Texture;



void main() {
	Colour = texture(Texture, v_TexCoord) * u_colour;
	
};