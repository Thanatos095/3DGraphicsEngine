#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Renderer.hpp>
class Camera{
    public:
        Camera(float FOV = 45.f, float near = 1.f, float far = 100.f, glm::vec3 position = glm::vec3{0.f, 0.f, 10.f}, glm::vec3 rotation = glm::vec3{0.f, -90.f, 0.f});
        void controller(float speed);
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec3 position);
        void moveX(float x);
        void moveY(float y);
        void moveZ(float z);
        // void move(float x, float y, float z);
        // void move(glm::vec3 position);
        void setRotation(float x, float y, float z);
        void setRotation(glm::vec3 rotation);
        void rotate(float x, float y, float z);
        void rotate(glm::vec3 position);
        void pan(float angle);
        void tilt(float angle);
        glm::mat4 getLookAt();
        const glm::mat4& getProjection();
        const glm::vec3& getPosition() const;
        const glm::vec3& getRotation() const;
    private:
        glm::vec3 m_rotation, m_position;
        float m_aspect_ratio, m_fov, m_near, m_far;
        glm::vec3 m_forward, m_right, m_up;
        glm::mat4 m_projection_matrix;
};

#endif
