#version 330 core

layout(location = 0) in vec4 VertexBufferData;
layout(location = 1) in vec2 texturecoords;

out vec2 v_TexCoord;


void main() {
gl_Position = VertexBufferData;
v_TexCoord = texturecoords;
}