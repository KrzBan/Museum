#include "Model.h"

#include <iostream>
#include <algorithm>
#include <numeric>

#include "ResourceManager.h"

Model::Model(const char* path, bool leftHanded) : transform{}, tiling{ 1.0f } {
    LoadModel(path, leftHanded);

    ResourceManager::AddModel(this);
}

Model::~Model() {
    ResourceManager::DeleteModel(this);
}

void Model::SetupModel(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    //calculate model's size, based on min and max vert position (like boundaries of a box around a model)
    auto xMinMax = std::minmax_element(vertices.begin(), vertices.end(), [](const Vertex& a, const Vertex& b) {return a.position.x < b.position.x; });
    auto yMinMax = std::minmax_element(vertices.begin(), vertices.end(), [](const Vertex& a, const Vertex& b) {return a.position.y < b.position.y; });
    auto zMinMax = std::minmax_element(vertices.begin(), vertices.end(), [](const Vertex& a, const Vertex& b) {return a.position.z < b.position.z; });
    transform.originalSize = glm::vec3{
       xMinMax.second->position.x - xMinMax.first->position.x, 
       yMinMax.second->position.y - yMinMax.first->position.y,
       zMinMax.second->position.z - zMinMax.first->position.z};
    transform.size = transform.originalSize;
    transform.originPoint = glm::vec3{ 
        std::midpoint(xMinMax.second->position.x, xMinMax.first->position.x),
        std::midpoint(yMinMax.second->position.y, yMinMax.first->position.y),
        std::midpoint(zMinMax.second->position.z, zMinMax.first->position.z) };


    VAO = std::make_shared<VertexArray>();
    VBO = std::make_shared<VertexBuffer>(&vertices[0], vertices.size() * sizeof(Vertex));
    EBO = std::make_shared<IndexBuffer>(&indices[0], indices.size());

    VAO->Bind();
    VAO->SetIndexBuffer(EBO);
    VAO->AddVertexBuffer(VBO);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    // tangents
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // tangents
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    VAO->Unbind();
}

void Model::LoadModel(std::string path, bool flipUVs){
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | (aiProcess_FlipUVs * flipUVs) | aiProcess_CalcTangentSpace );

    if (scene==nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << '\n';
        return;
    }
    m_Directory = path.substr(0, path.find_last_of('/'));

    std::vector<Vertex>     vertices;
    std::vector<uint32_t>   indices;

    ProcessNode(scene->mRootNode, scene, vertices, indices);
    SetupModel(vertices, indices);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices){
    //process all the node's m_Meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene, vertices, indices);
    }
    //continue for all children
    for (unsigned int i = 0; i < node->mNumChildren; i++){
        ProcessNode(node->mChildren[i], scene, vertices, indices);
    }
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices){

    for (unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        //process vertex positions
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        //normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        //tex coords (optional)
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        //tangents
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;
        //bitangents
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.bitangent = vector;

        vertices.push_back(vertex);
    }

    //process m_Indices
    uint32_t lastIndex = 0;
    if (indices.empty() == false) {
        lastIndex = indices.back() + 1;
    }
    for (size_t i = 0; i < mesh->mNumFaces; ++i){
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j] + lastIndex);
    }

    //process materials (textures)
    //actually dont
}

void Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName){

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < m_TexturesLoaded.size(); j++){
            if (std::strcmp(m_TexturesLoaded[j]->GetPath().data(), str.C_Str()) == 0){
                skip = true;
                break;
            }
        }
        if (skip == false){   // if texture hasn't been loaded already, load it
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(m_Directory + '/' + std::string{ str.C_Str() });
            if (texture->GetWidth() == 0) continue;
            texture->SetType(typeName);
            texture->SetPath(str.C_Str());
            m_TexturesLoaded.push_back(texture); // add to loaded m_Textures
        }
    }
}

void Model::Draw(const std::shared_ptr<Shader>& shader) {

    shader->Bind();
    shader->SetMat4f("u_Model", transform.transform);
    shader->SetFloat2("u_Tiling", tiling);
    shader->SetBool("u_UseSpecular", m_UseSpecular);
    shader->SetBool("u_UseNormal", m_UseNormal);
    shader->SetBool("u_UseRoughness", m_UseRoughness);
    shader->SetBool("u_UseAo", m_UseAo);
    shader->SetBool("u_ReceiveShadows", m_ReceiveShadows);


    uint32_t diffuseNr = 1;
    uint32_t specularNr = 1;
    uint32_t normalNr = 1;
    uint32_t roughNr = 1;
    uint32_t aoNr = 1;
    for (unsigned int i = 0; i < m_TexturesLoaded.size(); i++){
        // retrieve texture number (the N in diffuseTextureN)
        std::string number;
        std::string name = m_TexturesLoaded[i]->GetType();
        if (name == "textureDiffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "textureSpecular")
            number = std::to_string(specularNr++);
        else if (name == "textureNormal")
            number = std::to_string(normalNr++);
        else if (name == "textureRoughness")
            number = std::to_string(roughNr++);
        else if (name == "textureAo")
            number = std::to_string(aoNr++);

        shader->SetInt(name + number, i);
        m_TexturesLoaded[i]->Bind(i);
    }
    glActiveTexture(GL_TEXTURE0);

    //draw whole model
    VAO->Bind();
    glDrawElements(GL_TRIANGLES, VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
    VAO->Unbind();
}

void Model::InsertTexture(std::string path, TEX_TYPE type) {

    std::shared_ptr<Texture> texture = std::make_shared<Texture>(path);
    if (texture->GetWidth() == 0) return;

    switch (type) {
    case TEX_TYPE::TEX_DIFFUSE:
        texture->SetType("textureDiffuse");
        break;
    case TEX_TYPE::TEX_SPECULAR:
        texture->SetType("textureSpecular");    //doubles as metalic
        m_UseSpecular = true;
        break;
    case TEX_TYPE::TEX_NORMAL:
        texture->SetType("textureNormal");
        m_UseNormal = true;
        break;
        case TEX_TYPE::TEX_ROUGHNESS:
        texture->SetType("textureRoughness");
        m_UseRoughness = true;
        break;
    case TEX_TYPE::TEX_AO:
        texture->SetType("textureAo");
        m_UseAo = true;
        break;
    default:
        std::cerr << "Unsupported texture type.\n";
    }

    texture->SetPath(path);
    m_TexturesLoaded.push_back(texture);
}