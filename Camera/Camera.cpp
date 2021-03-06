#include <float.h>
#include <math.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "Camera.h"
#include "Settings.h"
Camera::Camera()
{
    m_aspectRatio = 1.f;
    m_near = 1.f;
    m_far = 30.f;
    m_thetaH = glm::radians(60.f);
    m_thetaW = 2 * glm::atan(m_aspectRatio * glm::tan(m_thetaH/2));
    m_eye = glm::vec4(0.f, 0.f, 2.f, 1.f);
    m_up = glm::vec4(0.f, 1.f, 0.f, 0.f);
    m_w = glm::normalize(glm::vec4(2.f, 2.f, 2.f, 0));
    m_v = glm::normalize(m_up - glm::dot(m_up,m_w)*m_w);
    m_u = glm::normalize(glm::vec4(glm::cross(glm::vec3(m_v), glm::vec3(m_w)), 0));
    updateProjectionMatrix();
    updateViewMatrix();
}


void Camera::setAspectRatio(float a)
{
    m_aspectRatio = a;
    m_thetaW = 2 * glm::atan(m_aspectRatio * glm::tan(m_thetaH/2));
    updateProjectionMatrix();
}

glm::mat4x4 Camera::getProjectionMatrix() const {
    return m_perspectiveTransformation*m_scaleMatrix;
}

glm::mat4x4 Camera::getViewMatrix() const {
    return m_rotationMatrix*m_translationMatrix;
}

glm::mat4x4 Camera::getScaleMatrix() const {
    return m_scaleMatrix;
}

glm::mat4x4 Camera::getPerspectiveMatrix() const {
    return m_perspectiveTransformation;
}

glm::vec4 Camera::getPosition() const {
    return m_eye;
}

glm::vec4 Camera::getLook() const {
    return -m_w;
}

glm::vec4 Camera::getUp() const {
    return m_up;
}

glm::vec4 Camera::getU() const {
    return m_u;
}

glm::vec4 Camera::getV() const {
    return m_v;
}

glm::vec4 Camera::getW() const {
    return m_w;
}

float Camera::getAspectRatio() const {
    return m_aspectRatio;
}

float Camera::getHeightAngle() const {
    return m_thetaH;
}

void Camera::updatePosition(float x, float y, float z) {
    m_eye = glm::vec4(x, y, z, 1.f);
    updateViewMatrix();
}


void Camera::orientLook(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &up) {
    m_eye = eye;
    m_up = glm::normalize(up);
    m_w = -glm::normalize(look);
    glm::vec4 vCalc = m_up - glm::dot(m_up,m_w)*m_w;
    m_v = glm::normalize(vCalc);
    m_u = glm::normalize(glm::vec4(glm::cross(glm::vec3(m_v), glm::vec3(m_w)), 0));
    updateViewMatrix();
    updateProjectionMatrix();
}

void Camera::setHeightAngle(float h) {
    m_thetaH = glm::radians(h);
    m_thetaW = 2 * glm::atan(m_aspectRatio * glm::tan(m_thetaH/2));
    updateProjectionMatrix();
}

/*
 * Probably won't need to implement this stuff
 *
void Camera::translate(const glm::vec4 &v) {
    m_eye += v;
    updateViewMatrix();

}

void Camera::rotateU(float degrees) {
    // @TODO: [] Fill this in...
    glm::vec4 vNot = m_v;
    glm::vec4 wNot = m_w;
    m_v = wNot * glm::sin(glm::radians(degrees)) + vNot * glm::cos(glm::radians(degrees));
    m_w = wNot * glm::cos(glm::radians(degrees)) - vNot * glm::sin(glm::radians(degrees));
    updateViewMatrix();

}

void Camera::rotateV(float degrees) {
    // @TODO: [] Fill this in...
    glm::vec4 uNot = m_u;
    glm::vec4 wNot = m_w;
    m_u= uNot * glm::cos(glm::radians(degrees)) - wNot * glm::sin(glm::radians(degrees));
    m_w = uNot * glm::sin(glm::radians(degrees)) + wNot * glm::cos(glm::radians(degrees));
    updateViewMatrix();

}

void Camera::rotateW(float degrees) {
    // @TODO: [] Fill this in...
    glm::vec4 uNot = m_u;
    glm::vec4 vNot = m_v;
    m_u = (uNot * glm::cos(-glm::radians(degrees))) - (vNot * glm::sin(-glm::radians(degrees)));
    m_v = (uNot * glm::sin(-glm::radians(degrees))) + (vNot * glm::cos(-glm::radians(degrees)));
    updateViewMatrix();

}
*/
void Camera::setClip(float nearPlane, float farPlane) {
    m_near = nearPlane;
    m_far = farPlane;
    updateProjectionMatrix();
}

void Camera::updateProjectionMatrix() {
    updateScaleMatrix();
    updatePerspectiveMatrix();

}
void Camera::updatePerspectiveMatrix() {
    m_perspectiveTransformation = glm::transpose(glm::mat4(1, 0, 0, 0,
                                                           0, 1, 0, 0,
                                                           0, 0, -1/((-m_near/m_far) + 1), (-m_near/m_far)/((-m_near/m_far) + 1),
                                                           0, 0, -1, 0));

}
void Camera::updateScaleMatrix() {
    m_scaleMatrix = glm::transpose(glm::mat4((1/(glm::tan(m_thetaW/2))/m_far), 0, 0, 0,
                                             0, (1/(glm::tan(m_thetaH/2))/m_far), 0, 0,
                                             0, 0, 1/m_far, 0,
                                             0, 0, 0, 1));

}
void Camera::updateViewMatrix(){
    updateTranslationMatrix();
    updateRotationMatrix();
}
void Camera::updateRotationMatrix(){
    m_rotationMatrix = glm::transpose(glm::mat4(m_u.x, m_u.y, m_u.z, 0,
                                                m_v.x, m_v.y, m_v.z, 0,
                                                m_w.x, m_w.y, m_w.z, 0,
                                                0, 0, 0, 1));

}
void Camera::updateTranslationMatrix(){
    m_translationMatrix = glm::transpose(glm::mat4(1, 0, 0, -m_eye.x,
                                                   0, 1, 0, -m_eye.y,
                                                   0, 0, 1, -m_eye.z,
                                                   0, 0, 0, 1));
}
