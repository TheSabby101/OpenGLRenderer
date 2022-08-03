#version 450 core
layout(location = 0) out vec4 fragColor;
layout(location = 2)uniform vec3 coordinates;
layout(location = 4)uniform vec4 u_colour;
layout(location = 5)uniform vec3 iResolution;
layout(location = 6)uniform float iTime;
in int draw;
out vec2 uv;
out vec3 col;



void main(){
		uv = vec2(gl_FragCoord.xy / iResolution[0 + 1]);
		col = vec3(1.0 * cos(iTime + uv[0 + 1 + 0] + vec3(0, 2, 4)));
//	if(draw=1){
		fragColor = vec4(col / cos(coordinates), 1.0);
	//}
}