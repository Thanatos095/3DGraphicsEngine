#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include "../source/GLDebugger.cpp"

class Shader{
    public:
        Shader(const std::string &vertexShader, const std::string &fragmentShader);
        Shader();
        Shader(const Shader& shader) = delete;
        Shader& operator=(const Shader& shader) = delete;
        Shader& operator=(Shader&& shader);
        void create(const std::string &vertexShader, const std::string &fragmentShader);
        static Shader DefaultShader();
        ~Shader();
        void bind();
        unsigned int getId();
        void provideMat4f(const std::string & variableName,const glm::mat4 &mat);
        void provideVec4f(const std::string & variableName, float f0, float f1, float f2, float f3);
    private:
        std::unordered_map<std::string, int> locations;
        unsigned int shaderId;
        unsigned int compileShader(unsigned int type, const std::string &shader);
        int getLocation(const std::string& variableName);
};

#endif