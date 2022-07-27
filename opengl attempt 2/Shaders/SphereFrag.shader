#version 430 core

uniform vec2 Res;

float circleShape(float radius, vec2 position)
{
	float value = distance(position, vec2(0.5));
	return step(radius, value);
}
void main() {
	vec2 pixelCoord = gl_FragCoord.xy / Res;
	float circleWidth = 0.2;
	float circle = circleShape(circleWidth, pixelCoord);
	vec3 color = vec3(circle);
	gl_FragColor = vec4(color, 1.0);

};