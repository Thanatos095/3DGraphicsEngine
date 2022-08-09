#ifndef SCENE_HPP
#define SCENE_HPP

#include <SceneObject.hpp>
#include <list>

class Camera;
class Renderer;
class Scene{
    public:
        Scene();
        void AddObjectToScene(SceneObject &obj);
        void SetActiveCamera(Camera& cam);
        virtual void start() = 0;
        virtual void update() = 0;
    private:
        Camera *camera;
        std::list<SceneObject*> m_objects;
        friend class Renderer;
}; 

#endif