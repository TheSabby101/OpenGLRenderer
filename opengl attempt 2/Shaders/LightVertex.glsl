#version 450 core

in vec3 positions;
layout(location = 1)uniform mat4 CamMat;
layout(location = 2)uniform vec3 coordinates;
layout(location = 3)uniform vec3 scale;
out int draw;

bool in_frustum(mat4 M, vec3 p){
    vec4 Pclip = M * vec4(p, 1.0);
    return abs(Pclip[0]) < Pclip[3] &&
        abs(Pclip[1]) < Pclip[3] &&
        0 < Pclip[2] &&
        Pclip[2] < Pclip[3];
}

void main() {
   // if (in_frustum(CamMat, positions)) {
        gl_Position = CamMat * vec4(positions * scale + coordinates, 1.0);
     //   int draw = 1;
   // }
   //// else
   // {
   //     int draw = 0;
   // }
}
