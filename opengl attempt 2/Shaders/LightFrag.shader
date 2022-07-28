#version 430 core

layout(location = 3)uniform vec3 coordinates;
layout(location = 4)uniform vec4 u_colour;
out vec4 Colour;

void main() {
	Colour = vec4(coordinates/10,1.0) * u_colour;
//	gl_FragColor = vec4(gl_FragCoord.xyz,1.0);
};