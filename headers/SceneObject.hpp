#ifndef SCENEOBJECT_HPP
#define SCENEOBJECT_HPP

#include "VertexArray.hpp"
#include "Vector3.hpp"
#include <glm/glm.hpp>
class Renderer;
class SceneObject{
    public:
        SceneObject(const VertexArray &mesh);
        SceneObject();
        void setPosition(float x, float y, float z);
        void setSize(float x, float y, float z);
        void setRotate(float x, float y, float z);
        void move(float x, float y, float z);
        void rotate(float x, float y, float z);
        void scale(float x, float y, float z);
        
        void setPosition(glm::vec3 position);
        void setSize(glm::vec3 size);
        void setRotate(glm::vec3 rotation);
        void move(glm::vec3 position);
        void scale(glm::vec3 size);
        void rotate(glm::vec3 rotation);
        void setMesh(const VertexArray &mesh);
        const glm::vec3& getPosition() const;
        const glm::vec3& getRotation() const;
        const glm::vec3& getSize() const;
        VertexArray m_mesh;
    private:
        glm::vec3 m_position;
        glm::vec3 m_size;
        glm::vec3 m_rotation;
        friend Renderer;
};
#endif