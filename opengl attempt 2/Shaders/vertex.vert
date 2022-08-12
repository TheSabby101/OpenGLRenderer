#version 450 core

layout(location = 0)in vec3 positions;
layout(location = 1)in vec2 texturecoords;
layout(location = 2)in vec3 normals;

layout(std140, binding=3) buffer SSBO
{
  vec4 Coordsin[];
};




uniform mat4 CamMat;
uniform vec3 coordinates;
uniform vec3 scale;
uniform vec3 LightPos;
uniform mat4 CamPos;
uniform mat4 MousePos;
uniform vec2 TextureOffset;

out vec2 v_TexCoord;
out vec3 OutNormals;
out vec3 CurrentPosition;
out vec3 Coords;
out float Highlight;


void main()
{

   if(Coordsin[gl_InstanceID].w !=1.0)
   {
   Highlight = 0.0;
   }
   else
   {
   Highlight = 0.5;
   }

	
	Coords = Coordsin[gl_InstanceID].xyz;
	CurrentPosition = vec3(CamPos * vec4(positions, 1.0));
	v_TexCoord = texturecoords+TextureOffset;
	OutNormals = normals;
	
	gl_Position = CamMat * vec4((positions * (scale/Coordsin[gl_InstanceID].w)) + Coords, 1.0);

}