#define GLFW_DLL 
#include "../headers/Window.hpp"

void resize_event_callBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(size_t window_width, size_t window_height, const std::string &name){
    if (!glfwInit())
        throw std::runtime_error("Error initializing GLFW");
    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->m_monitor = glfwGetPrimaryMonitor();
    this->m_window = glfwCreateWindow(window_width, window_height, name.c_str(), NULL, NULL);
    glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
}
Window::Window(){
    if (!glfwInit())
        throw std::runtime_error("Error initializing GLFW");
    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_monitor = glfwGetPrimaryMonitor();
    this->m_window = glfwCreateWindow(glfwGetVideoMode(this->m_monitor)->width,
                                      glfwGetVideoMode(this->m_monitor)->height,
                                      "Default",
                                      glfwGetPrimaryMonitor(),
                                      NULL);
    glfwSwapInterval(1);
    if (!this->m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Error initializing window");
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(this->m_window);
    if(glewInit() != GLEW_OK){
		throw std::runtime_error("Error initializing GLEW");
    }
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    this->input.setTarget(this->m_window);
    glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Window::setSize(size_t window_width, size_t window_height){
    float MonitorWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    float MonitorHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
    float posx = MonitorWidth/2 - float(window_width)/2;
    float posy = MonitorHeight/2 - float(window_height)/2;
    glfwSetWindowMonitor(this->m_window, nullptr, posx, posy, window_width, window_height, glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate);
    glViewport(0, 0, window_width, window_height);
    glfwSetWindowSizeCallback(this->m_window, resize_event_callBack);
}
void Window::close(){
    glfwSetWindowShouldClose(this->m_window, 1);
    glfwDestroyWindow(this->m_window);
}
void Window::setClearColor(glm::vec4 color){
    glClearColor(color[0], color[1], color[2], color[3]);
}
void Window::clear(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
}
void Window::draw(VertexArray& vao){
    vao.bind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, vao.indices.size(), GL_UNSIGNED_INT, nullptr);
}
void Window::display(){
    glfwSwapBuffers(this->m_window);
}
void Window::pollEvents(){
    glfwPollEvents();
}
void Window::setTitle(const std::string &name){
    glfwSetWindowTitle(this->m_window, name.c_str());
}

bool Window::isOpen() const{
    return !glfwWindowShouldClose(this->m_window);
}
Input& Window::getInput(){
    return this->input;
}
size_t Window::getWindowWidth() const{
    int width, height;
    glfwGetWindowSize(this->m_window, &width, &height);
    // std::cout << "W: "<< width << '\n';
    return width;
}
size_t Window::getWindowHeight() const{
    int width, height;
    glfwGetWindowSize(this->m_window, &width, &height);
    // std::cout << "H: "<< height << '\n';
    return height;
}
Window::~Window(){
    glfwTerminate();
}