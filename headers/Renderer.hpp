#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <memory>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <VertexArray.hpp>
#include <Shader.hpp>
#include <SceneObject.hpp>
#include <Scene.hpp>
#include <Window.hpp>
#include <Input.hpp>
#include <Camera.hpp>

class Renderer : public Window
{
    public:
        static Renderer& getInstance();
        void mainLoop();
        void setScene(std::shared_ptr<Scene> scene);
        void setShader(Shader && shader);
        float getDeltaTime();
        ~Renderer();
    private:
        using Window::clear;
        using Window::draw;
        using Window::display;
        using Window::pollEvents;
        using Window::isOpen;
        glm::mat4 transform(const SceneObject& obj);
        float deltaTime;
        Shader defaultShader;
        std::shared_ptr<Scene> m_scene;
        Renderer();
    /*Singleton Methods*/
    private:
    public:
        Renderer(Renderer const&) = delete;
        void operator=(Renderer const&)  = delete;
};

inline Renderer& Engine = Renderer::getInstance();
inline Input& In = Renderer::getInstance().getInput();

#endif