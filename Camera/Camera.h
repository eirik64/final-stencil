#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>


class Camera {
public:
    Camera() ;
    ~Camera() {}

    // Sets the aspect ratio of this camera. Automatically called by the GUI when the window is
    // resized.
    virtual void setAspectRatio(float aspectRatio);

    // Returns the projection matrix given the current camera settings.
    virtual glm::mat4x4 getProjectionMatrix() const;

    // Returns the view matrix given the current camera settings.
    virtual glm::mat4x4 getViewMatrix() const;

    // Returns the matrix that scales down the perspective view volume into the canonical
    // perspective view volume, given the current camera settings.
    virtual glm::mat4x4 getScaleMatrix() const;

    // Returns the matrix the unhinges the perspective view volume, given the current camera
    // settings.
    virtual glm::mat4x4 getPerspectiveMatrix() const;

    // Returns the current position of the camera
    glm::vec4 getPosition() const;

    virtual void mouseScrolled(int delta);
    void updateMatrices();
    void updatePosition(float x, float y, float z);

private:
    void updateProjectionMatrix();
    void updateViewMatrix();


    float m_aspectRatio;
    float m_near;
    float m_far;
    glm::mat4 m_translationMatrix;
    glm::mat4 m_perspectiveTransformation;
    glm::mat4 m_scaleMatrix;
    glm::mat4 m_rotationMatrix;
    float m_thetaH;
    float m_thetaW;
    glm::vec4 m_eye;
    glm::vec4 m_up;
    glm::vec4 m_u;
    glm::vec4 m_v;
    glm::vec4 m_w;
};

#endif // CAMERA_H
