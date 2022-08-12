#version 430 core
layout(location = 0)out vec4 fragColor;

uniform vec3 coordinates;
uniform float iTime;
uniform vec3 iResolution;
//uniform sampler2D Texture;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 LightPos;


out vec4 Colour;


float circleShape(float radius, vec2 position)
{
	float value = distance(position, vec2(0.5));
	return step(radius, value);
}
vec4 circle(vec2 uv, vec2 pos, float rad, vec3 color) {
	float d = length(pos - uv) - rad;
	float t = clamp(d, 0.0, 1.0);
	return vec4(color, 1.0 - t);
}

void main() 
{

	vec2 uv = gl_FragCoord.xy;
	vec2 center = iResolution.xy * 0.5;
	float radius = 0.05 * iResolution.y;

    // Background layer
	vec4 layer1 = vec4(0.0,1.0,1.0,0.0);
	
	// Circle
	vec3 red = vec3(225.0, 95.0, 60.0);
	vec4 layer2 = circle(uv, center, radius, red);
	
	// Blend the two
	fragColor = mix(layer1, layer2, layer2.a);

}