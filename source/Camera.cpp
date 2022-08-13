#include <Camera.hpp>
Camera::Camera(float FOV, float near, float far, glm::vec3 position, glm::vec3 rotation)
:
    m_rotation(glm::vec3{0.f, 0.f, 0}),
    m_position(position),
    m_aspect_ratio(float(Engine.getWindowWidth())/ Engine.getWindowHeight()),
    m_fov(FOV),
    m_near(near),
    m_far(far),
    m_forward{0, 0, -1},
    m_right{-1, 0, 0},
    m_up{0, 1, 0}
{
    this->m_projection_matrix = glm::perspective(this->m_fov, this->m_aspect_ratio, this->m_near, this->m_far);
}
void Camera::controller(float speed){
    speed *=Engine.getDeltaTime();
    const float camSpeed = 3*speed;
    static glm::vec2 lastMousePos(Engine.getWindowWidth()/2, Engine.getWindowHeight()/2);
    glm::vec2 rot = (lastMousePos - In.getMousePosition()) * 0.1f;
    lastMousePos = In.getMousePosition();
    
    this->m_rotation[0] -= rot[1];
    this->m_rotation[1] -= rot[0];

    if(In.isKeyPressed(Input::Key::W)){
        this->moveZ(speed);
    }
    if(In.isKeyPressed(Input::Key::S)){
        this->moveZ(-speed);
    }
    if(In.isKeyPressed(Input::Key::A)){
        this->moveX(speed);
    }
    if(In.isKeyPressed(Input::Key::D)){
        this->moveX(-speed);
    }
    if(In.isKeyPressed(Input::Key::UP)){
        this->moveY(speed);
    }
    if(In.isKeyPressed(Input::Key::DOWN)){
        this->moveY(-speed);
    }
}
void Camera::setPosition(float x, float y, float z){
    this->m_position = {x, y, z};
}
void Camera::setPosition(glm::vec3 position){
    this->m_position = position;
}
void Camera::moveX(float x){
    this->m_position += this->m_right  * x;
}
void Camera::moveY(float y){
    this->m_position += this->m_up  * y;
}
void Camera::moveZ(float z){
    this->m_position += this->m_forward  * z;
}
void Camera::setRotation(float x, float y, float z){
    this->m_rotation = {x, y, z};
}
void Camera::setRotation(glm::vec3 rotation){
    this->m_rotation = rotation;
}
void Camera::rotate(float x, float y, float z){
    this->m_rotation += glm::vec3{x, y, z};
}
void Camera::rotate(glm::vec3 rotation){
    this->m_rotation += rotation;
}
void Camera::pan(float angle){
    
    this->m_rotation[1] += angle;
}
void Camera::tilt(float angle){
    this->m_rotation[0] += angle;
}
glm::mat4 Camera::getLookAt(){
    if(this->m_rotation[0] > 89.999) this->m_rotation[0] = 89.999;
    if(this->m_rotation[0] < -89.999) this->m_rotation[0] = -89.999;

    this->m_forward = glm::normalize(glm::toMat3(glm::quat(glm::radians(-m_rotation))) * glm::vec3(0, 0, -1));
    this->m_right = glm::normalize(glm::cross(this->m_forward, glm::vec3{0, -1, 0}));        
    this->m_up = glm::normalize(glm::cross(this->m_forward, this->m_right));

    return glm::lookAt(
        this->m_position,
        this->m_position + this->m_forward,
        glm::vec3{0, 1, 0}
    );
}
const glm::mat4& Camera::getProjection(){
    const float newAspectRatio = float(Engine.getWindowWidth())/ Engine.getWindowHeight();
    if(this->m_aspect_ratio != newAspectRatio){
        this->m_aspect_ratio = newAspectRatio;
        this->m_projection_matrix = glm::perspective(this->m_fov, this->m_aspect_ratio, this->m_near, this->m_far);
    }
    return this->m_projection_matrix;
}
const glm::vec3& Camera::getPosition() const{
    return this->m_position;
}
const glm::vec3& Camera::getRotation() const{
    return this->m_rotation;
}