#include <Camera.hpp>
Camera::Camera(float FOV, float near, float far, glm::vec3 position, glm::vec3 rotation)
:
    m_rotation(glm::vec3{0.f, 0.f, 0}),
    m_position(position),
    m_aspect_ratio(float(Renderer.getWindowWidth())/ Renderer.getWindowHeight()),
    m_fov(FOV),
    m_near(near),
    m_far(far){
    this->m_projection_matrix = glm::perspective(this->m_fov, this->m_aspect_ratio, this->m_near, this->m_far);
}
void Camera::controller(const float speed){

    static glm::vec2 lastMousePos(Renderer.getWindowWidth()/2, Renderer.getWindowHeight()/2);
    glm::vec2 rot = (lastMousePos - Input.getMousePosition()) * 0.1f;
    lastMousePos = Input.getMousePosition();
    this->m_rotation[0] += rot[1];
    this->m_rotation[1] += rot[0];
    
    if(Input.isKeyPressed(Input::Key::W)){
        this->move(glm::vec3(0, 0, -1) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::A)){
        this->move(glm::vec3(-1, 0, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::D)){
        this->move(glm::vec3(1, 0, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::S)){
        this->move(glm::vec3(0, 0, 1) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::UP)){
        this->move(glm::vec3(0, 1, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::DOWN)){
         this->move(glm::vec3(0, -1, 0) * speed * Renderer.getDeltaTime());
    }
    // if(Input.isKeyPressed(Input::Key::KP_8)){
    //     this->rotate(glm::vec3(-1, 0, 0) * speed * 20.f * Renderer.getDeltaTime());
    // }
    // if(Input.isKeyPressed(Input::Key::KP_2)){
    //     this->rotate(glm::vec3(1, 0, 0) * speed * 20.f * Renderer.getDeltaTime());
    // }
    // if(Input.isKeyPressed(Input::Key::KP_4)){
    //     this->rotate(glm::vec3(0, -1, 0) * speed * 20.f* Renderer.getDeltaTime());
    // }
    // if(Input.isKeyPressed(Input::Key::KP_6)){
    //     this->rotate(glm::vec3(0, 1, 0) * speed * 20.f * Renderer.getDeltaTime());
    // }
}
void Camera::setPosition(float x, float y, float z){
    this->m_position = {x, y, z};
}
void Camera::setPosition(glm::vec3 position){
    this->m_position = position;
}
void Camera::move(float x, float y, float z){
    this->m_position += glm::vec3{x, y, z};
}
void Camera::move(glm::vec3 position){
    this->m_position += position;
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

    glm::vec3 transformed_position = glm::toMat3(glm::quat(glm::radians(m_rotation))) * this->m_position;
    glm::vec3 transformed_forward_direction = glm::normalize(glm::toMat3(glm::quat(glm::radians(m_rotation))) * glm::vec3(0, 0, -1));
    return glm::lookAt(
        transformed_position,
        transformed_position + transformed_forward_direction,
        glm::vec3{0.f, 1.f, 0.f}
    );
}
const glm::mat4& Camera::getProjection(){
    const float newAspectRatio = float(Renderer.getWindowWidth())/ Renderer.getWindowHeight();
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