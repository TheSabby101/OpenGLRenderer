#version 430 core

layout(location = 0)in vec3 positions;
layout(location = 1)in vec2 texturecoords;
out vec2 v_TexCoord;


layout(location = 2)uniform mat4 Model;
layout(location = 3)uniform mat4 View;
layout(location = 4)uniform mat4 Projection;





void main() {
	gl_Position = Projection * View * Model * vec4(positions, 1.0f);
	v_TexCoord = texturecoords;
};