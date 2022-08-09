#define GLFW_DLL 
#include "../headers/Input.hpp"

Input::Input(GLFWwindow * window) : m_window_ref(window)
{}
Input::Input() : m_window_ref(NULL){}
bool Input::isKeyPressed(Input::Key key){
    if(this->m_window_ref == NULL) throw std::runtime_error("Input target window not set!");
    return glfwGetKey(this->m_window_ref, int(key)) == GLFW_PRESS;
}
glm::vec2 Input::getMousePosition() const{
    double x, y;
    glfwGetCursorPos(this->m_window_ref, &x, &y);
    return glm::vec2{x, y};
}
void Input::setTarget(GLFWwindow *window){
    this->m_window_ref = window;
}