#version 450 core
layout(location = 0)out vec4 fragColor;



in vec2 v_TexCoord;
in vec3 OutNormals;
in vec3 CurrentPosition;
in vec3 Coords;
in float Highlight;

out vec4 Colour;
out vec2 uv;
out vec3 col;



uniform vec3 coordinates;
uniform float iTime;
uniform vec3 iResolution;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 LightPos;


uniform vec3 CamPos;
uniform sampler2D Texture;


void main()
{
	
   
	float ambientbase = 0.2;
	vec3 OutNormals = normalize(OutNormals-Coords);
	vec3 lightDirection = normalize(LightPos +Coords);
	float diffuse = max(dot(OutNormals, lightDirection), 0.0);
	float speclight = Highlight;
	vec3 viewDirection = normalize(Coords - CamPos);
	vec3 reflectionDirection = reflect(-lightDirection, OutNormals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8);
	float specular = specAmount * speclight;
	fragColor = texture(Texture, v_TexCoord) *vec4(lightColor,1000.0) / (diffuse+ambientbase+specular)/5;
}

