#include "../headers/Shader.hpp"
Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader)
{
    this->shaderId = 0;
    this->create(vertexShader, fragmentShader);
}
Shader::Shader() : shaderId(0){}
Shader& Shader::operator=(Shader&& shader){
    std::swap(this->shaderId, shader.shaderId);
    this->locations.clear();
    return *this;
}
void Shader::create(const std::string &vertexShader, const std::string &fragmentShader){
    if(shaderId != 0) throw std::runtime_error("Shader was already created!");
    this->shaderId = glCreateProgram();
    unsigned int vs = this->compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(this->shaderId, vs);
    glAttachShader(this->shaderId, fs);
    glLinkProgram(this->shaderId);
    glValidateProgram(this->shaderId);
    glDeleteShader(vs);
    glDeleteShader(fs);

}
Shader Shader::DefaultShader(){
    const std::string vertexShader = R"(
	#version 330 core
	layout(location = 0) in vec3 vertexPosition_modelspace;
	layout(location = 1) in vec4 vertexColor;
	out vec4 fragmentColor;
	uniform mat4 MVP;
	void main(){	

		gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
		fragmentColor = vertexColor;
	}
	)";
    const std::string fragmentShader = R"(
	#version 330 core
	in vec4 fragmentColor;
	out vec4 color;

	void main(){
		color = fragmentColor;
	}
	)";
    return Shader(vertexShader, fragmentShader);
}
void Shader::bind(){
    glUseProgram(this->shaderId);
}
unsigned int Shader::getId(){
    return this->shaderId;
}
void Shader::provideMat4f(const std::string & variableName,const glm::mat4 &mat){

    int location = this->getLocation(variableName);
    /*1 is the number of matrices we are passing. 
     false means to not transpose it. If our matrix was row major we would have to transpose it(set it to true)
    */
    glUniformMatrix4fv(location, 1, false, &mat[0][0]);   
}
void Shader::provideVec4f(const std::string & variableName, float f0, float f1, float f2, float f3){
    int location = this->getLocation(variableName);
    glUniform4f(location, f0, f1, f2, f3);
}

unsigned int Shader::compileShader(unsigned int type, const std::string &shader){
    unsigned int id = glCreateShader(type);
    const char *src = shader.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char * message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << '\n';
        std::cout << message << '\n';
        glDeleteShader(id);
        delete[] message;
        return 0;
    }
    return id;
}
int Shader::getLocation(const std::string& variableName){
    auto it = this->locations.find(variableName);
    int res;
    if(it == this->locations.end()){
        res = glGetUniformLocation(this->shaderId, variableName.c_str());
        ASSERT(res != -1);
    }
    else res = (*it).second;
    return res;
}

Shader::~Shader(){
    if(this->shaderId != 0)
        glDeleteProgram(this->shaderId);
}