#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTan;
layout (location = 3) in vec2 aTCoords;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform float atextureSize;
out float textureSize;
out mat3 TBN;
out vec2 TCoords;
flat out int useTBN;
out vec3 Norm;
out float Dist;
out vec3 FragPos;
void main(){
   TCoords = aTCoords;
   textureSize = atextureSize;
   Norm =  mat3(transpose(inverse(model))) * aNorm;
   vec3 T = normalize(vec3(model * vec4(aTan,   0.0)));
   vec3 N = normalize(vec3(model * vec4(aNorm,    0.0)));
   T = normalize(T - dot(T, N) * N);
   vec3 B = cross(N,T);
   TBN = mat3( T, B, N);
   useTBN=1;

   gl_Position = projection * view * model * vec4(aPos, 1.0);

   FragPos = vec3(model * vec4(aPos,1.0));
}
