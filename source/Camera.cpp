#include <Camera.hpp>
Camera::Camera(float FOV, float near, float far, glm::vec3 position, glm::vec3 rotation)
:
    m_rotation(glm::vec3{0.f, 0.f, 0}),
    m_position(position),
    m_aspect_ratio(float(Renderer.getWindowWidth())/ Renderer.getWindowHeight()),
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
    speed *=Renderer.getDeltaTime();
    const float camSpeed = 3*speed;
    static glm::vec2 lastMousePos(Renderer.getWindowWidth()/2, Renderer.getWindowHeight()/2);
    glm::vec2 rot = (lastMousePos - Input.getMousePosition()) * 0.1f;
    lastMousePos = Input.getMousePosition();
    
    this->m_rotation[0] -= rot[1];
    this->m_rotation[1] -= rot[0];

    if(Input.isKeyPressed(Input::Key::W)){
        this->moveZ(speed);
        // this->move(glm::vec3(0, 0, -1) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::S)){
        this->moveZ(-speed);
        // this->move(glm::vec3(0, 0, 1) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::A)){
        this->moveX(speed);
        // this->move(glm::vec3(-1, 0, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::D)){
        this->moveX(-speed);
        // this->move(glm::vec3(1, 0, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::UP)){
        this->moveY(speed);
        // this->move(glm::vec3(0, 1, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::DOWN)){
        this->moveY(-speed);
        //  this->move(glm::vec3(0, -1, 0) * speed * Renderer.getDeltaTime());
    }
    if(Input.isKeyPressed(Input::Key::KP_8)){
        this->rotate(glm::vec3(-1, 0, 0) * camSpeed);
    }
    if(Input.isKeyPressed(Input::Key::KP_2)){
        this->rotate(glm::vec3(1, 0, 0) * camSpeed);
    }
    if(Input.isKeyPressed(Input::Key::KP_4)){
        this->rotate(glm::vec3(0, -1, 0) *camSpeed);
    }
    if(Input.isKeyPressed(Input::Key::KP_6)){
        this->rotate(glm::vec3(0, 1, 0) * camSpeed);
    }
}
void Camera::setPosition(float x, float y, float z){
    this->m_position = {x, y, z};
}
void Camera::setPosition(glm::vec3 position){
    this->m_position = position;
}
// void Camera::move(float x, float y, float z){
//     this->m_position += glm::vec3{x, y, z};
// }
// void Camera::move(glm::vec3 position){
//     this->m_position += position;
// }
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
    // std::cout << glm::to_string(this->m_rotation) << '\n';
    
    if(this->m_rotation[0] > 89.999) this->m_rotation[0] = 89.999;
    if(this->m_rotation[0] < -89.999) this->m_rotation[0] = -89.999;

    // // glm::vec3 transformed_position = glm::toMat3(glm::quat(glm::radians(m_rotation))) * this->m_position;
    // // glm::vec3 transformed_forward_direction = glm::normalize(glm::toMat3(glm::quat(glm::radians(m_rotation))) * glm::vec3(0, 0, -1));
    // glm::vec3 right, up, forward;
    // // forward = glm::normalize(glm::toMat4(glm::quat(glm::radians(m_rotation))) * glm::vec4(0, 0, -1, 0));
    // right = glm::normalize(glm::cross(forward, glm::vec3{0, 1, 0}));
    // up = glm::normalize(glm::cross(forward, right));
    // // this->m_basis = glm::row(m_basis, 0, right);

    // glm::vec3 camZ = glm::vec3(0, 0, -1);
    // glm::vec3 forward = glm::normalize(glm::vec3{0, 0, -1});
	glm::vec3 direction(
		cos(this->m_rotation[0]) * sin(this->m_rotation[1]), 
		sin(this->m_rotation[0]),
		cos(this->m_rotation[0]) * cos(this->m_rotation[1])
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(this->m_rotation[1] - 3.14f/2.0f), 
		0,
		cos(this->m_rotation[1] - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

    this->m_forward = glm::normalize(glm::toMat3(glm::quat(glm::radians(-m_rotation))) * glm::vec3(0, 0, -1));
    this->m_right = glm::normalize(glm::cross(this->m_forward, glm::vec3{0, -1, 0}));        
    this->m_up = glm::normalize(glm::cross(this->m_forward, this->m_right));
    // glm::vec3 up = glm::cross(forward, right); // Ideally it is normalized
    // glm::mat4 mat;
    // mat[0] = glm::vec4(right, 0); // Set first column [Ux; Uy; Uz; 0]
    // mat[1] = glm::vec4(up, 0); // Set second column [Vx; Vy; Vz; 0]
    // mat[2] = glm::vec4(forward, 0); // Set third column [Wx; Wy; Wz; 0]
    // mat[3] = glm::vec4(-this->m_position, 1); // Set 4th column
    // return  glm::translate(glm::mat4(1.f), this->m_position) * glm::toMat4(glm::quat(glm::radians(-m_rotation))) * glm::translate(glm::mat4(1.f), -this->m_position);
    // return mat;
    // // this->m_basis[0][0] = right[0];
    // // this->m_basis[1][0] = right[1];
    // // this->m_basis[2][0] = right[2];

    // // this->m_basis[0][1] = up[0];
    // // this->m_basis[1][1] = up[1];
    // // this->m_basis[2][1] = up[2];

    // // this->m_basis[0][2] = forward[0];
    // // this->m_basis[1][2] = forward[1];
    // // this->m_basis[2][2] = forward[2];
    
    // glm::vec3 transformed_position = glm::toMat3(glm::quat(glm::radians(m_rotation))) * this->m_position;    
    // glm::vec3 transformed_forward_direction = glm::normalize(glm::toMat3(glm::quat(glm::radians(m_rotation))) * glm::vec3(0, 0, -1));;
    // return glm::lookAt(
    //     transformed_position,
    //     transformed_position + transformed_forward_direction,
    //     glm::vec3{0.f, 1.f, 0.f}
    // );
    return glm::lookAt(
        this->m_position,
        this->m_position + this->m_forward,
        glm::vec3{0, 1, 0}
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