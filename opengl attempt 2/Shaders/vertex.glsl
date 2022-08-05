#version 450 core

layout(location = 0)in vec3 positions;
layout(location = 1)in vec2 texturecoords;
layout(location = 2)in vec3 normals;

uniform mat4 CamMat;
uniform vec3 coordinates;
uniform vec3 scale;
uniform vec3 LightPos;

out vec2 v_TexCoord;
out vec3 OutNormals;
out vec3 CurrentPosition;

void main()
{
	CurrentPosition = vec3(CamMat * vec4(positions, 1.0));
	v_TexCoord = texturecoords;
	OutNormals = normals;
	gl_Position = CamMat * vec4(positions * scale + coordinates, 1.0);
}