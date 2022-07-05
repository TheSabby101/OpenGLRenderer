#version 430 core

in vec2 v_TexCoord;
out vec4 Colour;


uniform sampler2D Texture;
//uniform vec4 u_colour;


void main() {
	Colour = texture(Texture, v_TexCoord);
	
};