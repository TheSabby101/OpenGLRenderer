#version 430 core

layout (location = 0) in vec4 positions;
layout (location = 1) in vec2 texturecoords;

out vec2 v_TexCoord;


void main() {

	gl_Position = positions;
	v_TexCoord = texturecoords;
};