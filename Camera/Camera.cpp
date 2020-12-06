#include <float.h>
#include <math.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "Camera.h"
#include "Settings.h"
Camera::Camera() :
    m_aspectRatio(1),
    m_angleX(0),
    m_angleY(0),
    m_zoomZ(-5),
    m_eye(glm::vec4(-2.f, 0.f, 0.f, 1.f))

{

}


void Camera::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;
    updateProjectionMatrix();
}

glm::mat4x4 Camera::getProjectionMatrix() const {
    return m_projectionMatrix;
}

glm::mat4x4 Camera::getViewMatrix() const {
    return m_viewMatrix;
}

glm::mat4x4 Camera::getScaleMatrix() const {
    return m_scaleMatrix;
}

glm::mat4x4 Camera::getPerspectiveMatrix() const {
    throw 0; // not implemented
}

glm::vec4 Camera::getPosition() const {
    return m_eye;
}

void Camera::updatePosition(float x, float y, float z) {
    m_angleX += x - m_eye.x;
    m_angleY += y - m_eye.y;
    if (m_angleX < -90.f) m_angleX = -90.f;
    if (m_angleX > 90.f) m_angleX = 90.f;

    m_eye = glm::vec4(x, y, z, 1.f);

    updateViewMatrix();
}


void Camera::mouseScrolled(int delta) {
    // Use an exponential factor so the zoom increments are small when we are
    // close to the object and large when we are far away from the object
    m_zoomZ *= powf(0.999f, delta);

    updateViewMatrix();
}

void Camera::updateMatrices() {
    updateProjectionMatrix();
    updateViewMatrix();
}

void Camera::updateProjectionMatrix() {
    // Make sure glm gets a far value that is greater than the near value.
    // Thanks Windows for making far a keyword!
    float farPlane = std::max(settings.cameraFar, settings.cameraNear + 100.f * FLT_EPSILON);
    float h = farPlane * glm::tan(glm::radians(settings.cameraFov * 0.5f));
    float w = m_aspectRatio * h;

    m_scaleMatrix = glm::scale(glm::vec3(1.f / w, 1.f / h, 1.f / farPlane));
    m_projectionMatrix = glm::perspective(
            glm::radians(settings.cameraFov), m_aspectRatio, settings.cameraNear, farPlane) * 0.02f;
}

void Camera::updateViewMatrix() {
    m_viewMatrix =
            glm::translate(glm::vec3(0.f, 0.f, m_zoomZ)) *
            glm::rotate(glm::radians(m_angleY), glm::vec3(0.f, 1.f, 0.f)) *
            glm::rotate(glm::radians(m_angleX), glm::vec3(1.f, 0.f, 0.f));
}

