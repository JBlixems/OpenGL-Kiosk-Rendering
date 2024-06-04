#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float width, float height)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(3.5f), mouseSensitivity(0.0025f) {
    updateCameraVectors();
    setProjection(80.0f, width / height, 0.1f, 100.0f);
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

glm::vec3 Camera::getFront() const{
    return front;
}

void Camera::setProjection(float fov, float aspect, float near, float far) {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::processKeyboard(int key, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (key == GLFW_KEY_W)
        position += front * velocity;
    if (key == GLFW_KEY_S)
        position -= front * velocity;
    if (key == GLFW_KEY_A)
        position -= right * velocity;
    if (key == GLFW_KEY_D)
        position += right * velocity;
    if (key == GLFW_KEY_D)
        position += right * velocity;
    if (key == GLFW_KEY_D)
        position += right * velocity;
    if (key == GLFW_KEY_LEFT_SHIFT)
        position += up * velocity;
    if (key == GLFW_KEY_LEFT_CONTROL)
        position -= up * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(this->front, worldUp));
    up = glm::normalize(glm::cross(right, this->front));
}

glm::vec3 Camera::getPosition() const{
    return position;
}