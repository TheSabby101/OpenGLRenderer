#version 430 core

layout(location = 0)in vec3 positions;
layout(location = 2)uniform mat4 CamMat;
layout(location = 3)uniform vec3 coordinates;
void main() {
	gl_Position = CamMat  * vec4(positions + coordinates, 1.0);
};