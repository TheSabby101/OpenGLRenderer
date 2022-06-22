#version 430 core
in vec2 v_TexCoord;
out vec4 color;


layout(location = 0) uniform sampler2D Texture;


void main() {
	
	vec4 TexColor = texture(Texture, v_TexCoord);
	color = TexColor;

};