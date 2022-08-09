#include "../headers/Scene.hpp"

Scene::Scene(){}
void Scene::AddObjectToScene(SceneObject & obj)
{
    this->m_objects.push_back(&obj);
}
void Scene::SetActiveCamera(Camera& cam){
    this->camera = &cam;
}
