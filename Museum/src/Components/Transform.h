#pragma once

#include "Utility.h"
#include "Scene.h"

#include <unordered_set>

class Transform {
private:
    Transform* m_Parent;
    std::unordered_set<Transform*> m_Children;

public:
    glm::mat4 transform;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 size;
    glm::vec3 originalSize;
    glm::vec3 originPoint;

    Transform(bool setParentToScene = true) : position{ glm::vec3(0.0f) }, rotation{ glm::vec3(0.0f) }, scale{ glm::vec3(1.0f) },
        size{ glm::vec3(0.0f) }, originalSize{ glm::vec3(0.0f) }, originPoint{ glm::vec3(0.0f) },
        transform{ glm::mat4(1.0f) } ,m_Parent{ nullptr }
    {
        if (setParentToScene) {
            SetParent(&Scene::GetTransform());
        }
    }

    void UpdateTransform() {
        glm::mat4 model{ 1.0f };
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);

        if (m_Parent)
            model = m_Parent->transform * model;

        transform = model;

       for (auto& child : m_Children) {
           child->UpdateTransform();
       }
    }

   void SetParent(Transform* newParent) {
       if (m_Parent) {
           m_Parent->m_Children.erase(this);
       }
       if (newParent) {
           newParent->m_Children.insert(this);
       }
   
       m_Parent = newParent;
   }

    void Translate(float x, float y, float z) { SetPosition(position.x + x, position.y + y, position.z + z); }
    void Translate(const glm::vec3& trans) { SetPosition(position + trans); }
    void SetPosition(float x, float y, float z) { SetPosition(glm::vec3{ x,y,z }); }
    void SetPosition(const glm::vec3& newPos) { position = newPos; }

    void Rotate(float x, float y, float z) { SetRotation(rotation.x + x, rotation.y + y, rotation.z + z); }
    void Rotate(const glm::vec3& rot) { SetRotation(rotation + rot); }
    void SetRotation(float x, float y, float z) { SetRotation(glm::vec3{ x,y,z }); }
    void SetRotation(const glm::vec3& newRot) { rotation = newRot; }

    void Scale(float x) { Scale(x, x, x); }
    void Scale(float x, float y, float z) { SetScale(scale.x * x, scale.y * y, scale.z * z); }
    void Scale(const glm::vec3& newScale) { SetScale(scale * newScale); }
    void SetScale(float uniformScale) { SetScale(glm::vec3{ uniformScale }); }
    void SetScale(float x, float y, float z) { SetScale(glm::vec3{ x,y,z }); }
    void SetScale(const glm::vec3& newScale) { scale = newScale; size = originalSize * scale; originPoint = originPoint * scale; }

    glm::vec3 OnGround() { return glm::vec3(position.x, size.y / 2 - originPoint.y, position.z); }
    void PutOnGround() { position.y = size.y / 2 - originPoint.y; }
};