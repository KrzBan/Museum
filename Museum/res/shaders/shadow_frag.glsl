#version 330 core

in vec4 FragPos;
flat in int LightIndex;

#define NR_POINT_LIGHTS STATIC_SHADOW_COUNT
uniform vec3 u_LightPos[NR_POINT_LIGHTS];
uniform float u_FarPlane;

out vec4 FragColor;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(FragPos.xyz - u_LightPos[LightIndex]);
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / u_FarPlane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;

   FragColor = vec4(lightDistance,lightDistance,lightDistance,1.0f);
}  