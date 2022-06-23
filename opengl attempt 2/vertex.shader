#version 430 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 texturecoords;

out vec2 v_TexCoord;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
gl_Position = Projection * View * Model * vec4(apos,1.0f);
v_TexCoord = texturecoords;
}