#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;  

out vec2 TexCoords;
out vec3 FragPos;  
out mat3 TBN;
out vec3 ViewDir;
out vec3 ViewPos;

uniform mat4 u_Model;
uniform mat4 u_ViewProj;

uniform vec2 u_Tiling;
uniform vec3 u_ViewPos;

void main()
{
    //TBN
    vec3 T = normalize(vec3(u_Model * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(u_Model * vec4(aNormal, 0.0)));
    T = normalize(T - dot(T, N) * N); // re-orthogonalize T with respect to N
    vec3 B = cross(N, T);  // then retrieve perpendicular vector B with the cross product of T and N
    TBN = transpose(mat3(T, B, N));

    TexCoords = vec2(aTexCoords.x * u_Tiling.x, aTexCoords.y * u_Tiling.y);    

    FragPos = vec3(u_Model * vec4(aPos, 1.0));
    ViewDir = TBN * normalize(u_ViewPos - FragPos);
    ViewPos = u_ViewPos;

    gl_Position = u_ViewProj * u_Model * vec4(aPos, 1.0);
}