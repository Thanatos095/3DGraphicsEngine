#include <iostream>
#include <memory>
#include <Renderer.hpp>
#include <Scene.hpp>
#include <SceneObject.hpp>
#include <VertexArray.hpp>
#include <Input.hpp>
#include <Window.hpp>
#include <Camera.hpp>
#include <glm/gtx/string_cast.hpp>
class myScene : public Scene{
	public:
		myScene() : 
			teapot(VertexArray::LoadFromFile("Models/teapot.obj")){
			this->AddObjectToScene(teapot);
			this->SetActiveCamera(cam);
		}
		void start(){
			teapot.setPosition(0, 0, 0);
			teapot.scale(0.7, 0.7, 0.7);
		}
		void update(){
			const float speed = 3.f;
			cam.controller(speed);
			teapot.rotate(glm::vec3(0, 90, 0) * Renderer.getDeltaTime());
		}
	private:
		Camera cam;
		SceneObject teapot;
};


int main(void)
{
	// Renderer.setSize(800, 600);
	Renderer.setTitle("Meow");
	Renderer.setScene(std::make_shared<myScene>());
	Renderer.mainLoop();
    return 0;
}



















	// Window window(700, 700, "Mahad");
	// SceneObject teapot = VertexArray::LoadFromFile("Models/teapot.obj");
	// Shader shader;
	// shader = Shader::DefaultShader();
	// shader.bind();
	// teapot.setPosition(0, 0 , -10);
	// while(window.isOpen()){
	// 	window.pollEvents();
	// 	window.clear();
	// 	teapot.rotate(0, 1, 0);
	// 	glm::mat4 MVP = transform(teapot);
	// 	shader.provideMat4f("MVP", MVP);
	// 	window.draw(teapot.m_mesh);
	// 	window.display();
	// }