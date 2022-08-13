#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "VertexArray.hpp"
#include "Input.hpp"
#include <iostream>
class Window{
    public:
        Window(size_t window_width, size_t window_height, const std::string &name);
        Window(); // Sets mode to full mode
        void setSize(size_t window_width, size_t window_height);
        void setTitle(const std::string &name);
        size_t getWindowWidth() const;
        size_t getWindowHeight() const;
        Input& getInput();
        ~Window();
        void close();
        void setClearColor(glm::vec4 color);
        void clear();
        void draw(VertexArray& vao);
        void display();
        void pollEvents();
        bool isOpen() const;
    private:
        Input input;
        GLFWwindow *m_window;
        GLFWmonitor *m_monitor;
};

#endif