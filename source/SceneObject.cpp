#include "../headers/SceneObject.hpp"

SceneObject::SceneObject(const VertexArray &mesh) : m_mesh(mesh),  m_position(1.f), m_size(1.f), m_rotation(1.f)
{
    
}
SceneObject::SceneObject(): m_position(1.f), m_size(1.f), m_rotation(1.f)
{

}

void SceneObject::setPosition(float x, float y, float z){
    this->m_position = {x, y, z};
}
void SceneObject::setSize(float x, float y, float z){
    this->m_size = {x, y, z};
}
void SceneObject::setRotate(float x, float y, float z){
    this->m_rotation = {x, y, z};
}
void SceneObject::move(float x, float y, float z){
    this->m_position += glm::vec3({x, y, z});
}
void SceneObject::rotate(float x, float y, float z){
    this->m_rotation += glm::vec3({x, y, z});
}
void SceneObject::scale(float x, float y, float z){
    this->m_size *= glm::vec3({x, y, z});
}
void SceneObject::setPosition(glm::vec3 position){
    this->m_position = position;
}
void SceneObject::setSize(glm::vec3 size){
    this->m_size = size;
}
void SceneObject::setRotate(glm::vec3 m_rotation){
    this->m_rotation = m_rotation;
}
void SceneObject::move(glm::vec3 position){
    this->m_position += position;
}
void SceneObject::scale(glm::vec3 size){
    this->m_size += size;
}
void SceneObject::rotate(glm::vec3 m_rotation){
    this->m_rotation += m_rotation;
}
void SceneObject::setMesh(const VertexArray &mesh){
    this->m_mesh = mesh;
}
const glm::vec3& SceneObject::getPosition() const{
    return this->m_position;
}
const glm::vec3& SceneObject::getRotation() const{
    return this->m_rotation;
}
const glm::vec3& SceneObject::getSize() const{
    return this->m_size;
}