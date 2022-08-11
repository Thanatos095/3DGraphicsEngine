#define GLFW_DLL 

#include "../headers/Renderer.hpp"

Renderer::Renderer() : m_scene(nullptr)
{
	this->defaultShader = Shader(Shader::DefaultShader());
}
Renderer::~Renderer(){}

class Renderer& Renderer::getInstance(){
	static Renderer instance;
    return instance;
}
void Renderer::setScene(std::shared_ptr<Scene> scene){
	this->m_scene = scene;
}

float Renderer::getDeltaTime(){
	return this->deltaTime;
}
void Renderer::setShader(Shader&& shader){
	this->defaultShader = std::move(shader);
}
glm::mat4 Renderer::transform(const SceneObject& obj){
	glm::mat4 Scale, Rotation, Translate;
	Scale = glm::scale(glm::mat4(1.f), obj.getSize());
	Rotation = glm::toMat4(glm::quat(glm::vec3{glm::radians(obj.getRotation())}));
	Translate= glm::translate(glm::mat4(1.f),obj.getPosition());
	glm::mat4 MVP = m_scene->camera->getProjection() * m_scene->camera->getLookAt() * Translate * Rotation * Scale;
	return MVP;	
}


void Renderer::mainLoop(){
	if(m_scene == nullptr)
		throw std::runtime_error("No active scene in the renderer.");

	defaultShader.bind();
	m_scene->start();
    while (this->isOpen())
    {	
		glfwSetTime(0);
		this->pollEvents();
		this->clear();
		m_scene->update();
		// std::cout << m_scene->m_objects.size()<< '\n';
		for(SceneObject* obj : m_scene->m_objects){
			glm::mat4 MVP = transform(*obj);
			defaultShader.provideMat4f("MVP", MVP);
			this->draw(obj->m_mesh);
	    }
		this->display();
		this->deltaTime = glfwGetTime();
	}
}