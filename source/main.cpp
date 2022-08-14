#include <iostream>
#include <memory>
#include <fstream>
#include <Renderer.hpp>
#include <Scene.hpp>
#include <SceneObject.hpp>
#include <VertexArray.hpp>
#include <Input.hpp>
#include <Texture.hpp>
#include <Camera.hpp>

class myScene : public Scene{
	public:
		myScene() : 
		// tex("Assets/wall.jpg"),
			cube(VertexArray::LoadFromFile("Models/cube.obj")){
			this->AddObjectToScene(cube);
			this->SetActiveCamera(cam);
			Textures.getTexture("Assets/wall.jpg");
		}
		void start(){
			
		}
		void update(){
			const float speed = 3.f;
			cam.controller(speed);
		}
	private:
		// Texture tex;
		Camera cam;
		SceneObject cube;
};


int main(void)
{
	Engine.setClearColor(glm::vec4{0.2f, 0.3f, 0.3f, 1.0f});
	Engine.setSize(800, 600);
	Engine.setShader(Shader::LoadFromFile("Shaders/Texture.shader"));
	Engine.setTitle("Meow");
	Engine.setScene(std::make_shared<myScene>());
	Engine.mainLoop();
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