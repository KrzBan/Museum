#pragma once

#include <string>
#include <vector>

#include "Utility.h"
#include "Texture.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Components/Transform.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

enum class TEX_TYPE {
    TEX_DIFFUSE,
    TEX_SPECULAR,
    TEX_NORMAL,
    TEX_ROUGHNESS,
    TEX_AO
};

class Model
{
public:
    Model(const char* path, bool flipUVs = true);
    ~Model();
    void Draw(const std::shared_ptr<Shader>& shader);

    void InsertTexture(std::string path, TEX_TYPE type = TEX_TYPE::TEX_DIFFUSE);

    Transform transform;
    glm::vec2 tiling;   //tiling ov UV maps
    bool castShadows = true;
    bool transparent = false;


private:

    std::string m_Directory;
    std::vector<std::shared_ptr<Texture>> m_TexturesLoaded;

    bool m_UseSpecular = false;
    bool m_UseNormal = false;
    bool m_UseRoughness = false;
    bool m_UseAo = false;
    bool m_ReceiveShadows = true;

    std::shared_ptr<VertexArray>    VAO;
    std::shared_ptr<VertexBuffer>   VBO;
    std::shared_ptr<IndexBuffer>    EBO;

public:
    void SetTiling(float uniformScale) { SetTiling(glm::vec2{ uniformScale }); }
    void SetTiling(float x, float y) { SetTiling(glm::vec2{ x, y }); }
    void SetTiling(const glm::vec2& newTiling) { tiling = newTiling; }

    void ReveiceShadows(bool value) { m_ReceiveShadows = value; }

private:void LoadModel(std::string path, bool flipUVs);
    
    void SetupModel(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    void LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    
};