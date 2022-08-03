#version 450 core
in vec3 positions;
in vec2 texturecoords;
layout(location = 2)uniform mat4 CamMat;
layout(location = 3)uniform vec3 coordinates;
uniform vec3 scale;
layout(location = 4)out vec2 v_TexCoord;

out vec2 TexCoords;

void main()
{
	gl_Position = CamMat * vec4(positions * scale + coordinates, 1.0);
	v_TexCoord = texturecoords;

}