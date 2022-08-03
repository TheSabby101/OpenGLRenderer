#version 450 core

in vec3 positions;
in vec2 texturecoords;

layout(location = 0)uniform mat4 CamMat;
layout(location = 1)uniform vec3 scale;
layout(location = 2)uniform vec3 coordinates;
//layout(location = 4)uniform vec2 texturecoords;
layout(location = 3)out vec2 v_TexCoord;

void main() {
	gl_Position = CamMat * vec4(positions * scale + coordinates, 1.0);
	v_TexCoord = texturecoords;
}