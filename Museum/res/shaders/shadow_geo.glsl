#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices=STATIC_LIGHT_18) out;

#define NR_POINT_LIGHTS STATIC_SHADOW_COUNT
uniform mat4 u_ShadowMatrices[NR_POINT_LIGHTS*6];

out vec4 FragPos;
flat out int LightIndex;

void main()
{
    for(int face = 0; face < NR_POINT_LIGHTS*6; ++face)
    {
        gl_Layer = face; // built-in variable that specifies to which face we render.
        LightIndex = face/6;
        for(int i = 0; i < 3; ++i) // for each triangle vertex
        {
            FragPos = gl_in[i].gl_Position;
            gl_Position = u_ShadowMatrices[face] * FragPos;
            EmitVertex();
        }    
        EndPrimitive();
    }
}  