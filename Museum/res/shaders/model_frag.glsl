#version 330 core

struct Material {
    float shininess;
}; 

struct PointLight {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 lightDir;
    bool castsShadows;
};

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;  
in vec3 ViewDir;
in vec3 ViewPos;
in mat3 TBN;

#define NR_POINT_LIGHTS STATIC_LIGHT_COUNT
uniform PointLight u_PointLights[NR_POINT_LIGHTS];  

uniform sampler2D textureDiffuse1;
uniform sampler2D textureSpecular1;
uniform sampler2D textureNormal1;

uniform Material u_Material;

uniform sampler2DArrayShadow textureDepth;
uniform float u_FarPlane;

uniform float u_Transparency;

uniform bool u_DrawShadows;
uniform bool u_UseLights;
uniform bool u_SoftShadows;
uniform bool u_ReceiveShadows;

uniform bool u_UseSpecular;
uniform bool u_UseNormal;

vec3 SampleCube(const vec3 v, const int index);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, int index); 
float CalculateShadow(vec3 lightPos, int index, vec3 normal);

void main()
{        
    vec3 norm = vec3(0,0,0);
    if(u_UseNormal)
        norm = texture(textureNormal1, TexCoords).rgb;
    norm = normalize(norm * 2.0 - 1.0); 

    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    if(u_UseLights){
        int index = 0;  //depthMap index, lights that dont cast shadows dont use it
        for(int i = 0; i < NR_POINT_LIGHTS; i++){
            result += CalcPointLight(u_PointLights[i], norm, ViewDir, index);     
            if( u_PointLights[i].castsShadows) ++index;
        }
    }
    else{
        result  = vec3(texture(textureDiffuse1, TexCoords));
    }
    
    FragColor = vec4(result, u_Transparency);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, int index)
{
    vec3 lightDir = TBN * normalize(light.position - FragPos);

    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    //specular shading
    //vec3 reflectDir = reflect(-lightDir, normal); //phong
    vec3 halfwayDir = normalize(lightDir + viewDir);  //blinn-phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), u_Material.shininess);
    
    //attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / distance;
    
    vec3 textureColor = vec3(texture(textureDiffuse1, TexCoords));
    vec3 textureSpecular =  vec3(0,0,0);
    if(u_UseSpecular)
        textureSpecular = vec3(texture(textureSpecular1, TexCoords));

    vec3 ambient  = light.ambient  * textureColor;
    vec3 diffuse  = light.diffuse  * diff * textureColor;
    vec3 specular = light.specular * spec * textureSpecular;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    float shadow = 0;
    if(u_DrawShadows && u_ReceiveShadows && light.castsShadows)
        shadow = CalculateShadow(light.position, index, normal);

    return (ambient + (1.0 - shadow) * (diffuse + specular));
    
} 

vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float CalculateShadow(vec3 lightPos, int index, vec3 normal){   

    if(!u_SoftShadows){
        float shadow = 0.0;
        vec3 fragToLight = FragPos - lightPos;
        
        float bias = 0.2; 
        float currentDepth = length(fragToLight);       
        
        vec3 sample = SampleCube(fragToLight, index);
        float closestDepth = texture(textureDepth, vec4(sample, length(fragToLight)/u_FarPlane));
        closestDepth *= u_FarPlane;
        shadow += currentDepth - bias > closestDepth ? 1.0 : 0.0;    
               
        return shadow;
    }
    else{
        vec3 fragToLight = FragPos - lightPos; 
        float currentDepth = length(fragToLight);  
        
        float shadow = 0.0;
        float bias = 0.15;
        float viewDistance = length(ViewPos - FragPos);
        float diskRadius = (1.0 + (viewDistance / u_FarPlane)) / 100.0;

        float distanceTreshold = 2.0/viewDistance;
        int samples = int(20.0 * distanceTreshold);
        if(samples < 4) samples = 1;
        else if(samples > 16) samples = 16;

        for(int i = 0; i < samples;++i){
            vec3 sample = SampleCube(fragToLight + gridSamplingDisk[i] * diskRadius, index);
            float closestDepth = texture(textureDepth, vec4(sample, length(fragToLight)/u_FarPlane));
            closestDepth *= u_FarPlane;
            if(currentDepth - bias > closestDepth)
                shadow += 1.0;
        }
        shadow /= float(samples);

        return shadow;
    }
    return 0; 
}

//bless this man
//https://www.gamedev.net/forums/topic/687535-implementing-a-cube-map-lookup-function/
vec3 SampleCube( const vec3 v, const int index)
{
	vec3 vAbs = abs(v);
    float faceIndex;
	float ma;
	vec2 uv;
	if(vAbs.z >= vAbs.x && vAbs.z >= vAbs.y)
	{
		faceIndex = v.z < 0.0 ? 5.0 : 4.0;
		ma = 0.5/vAbs.z;
		uv = vec2(v.z < 0.0 ? -v.x : v.x, -v.y);
	}
	else if(vAbs.y >= vAbs.x)
	{
		faceIndex = v.y < 0.0 ? 3.0 : 2.0;
		ma = 0.5/vAbs.y;
		uv = vec2(v.x, v.y < 0.0 ? -v.z : v.z);
	}
	else
	{
		faceIndex = v.x < 0.0 ? 1.0 : 0.0;
		ma = 0.5/vAbs.x;
		uv = vec2(v.x < 0.0 ? v.z : -v.z, -v.y);
	}

    vec2 result = uv * ma + 0.5;
	return vec3(result.xy, faceIndex + 6*index);
}