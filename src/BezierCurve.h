#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "Camera/Camera.h"
#include "GL/glew.h"

#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

class BezierCurve
{
public:
    BezierCurve(Camera camera);

    glm::vec4 PointOnCurve(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, float time);
    void moveCamera();

private:

    Camera m_camera;
    glm::vec4 m_startPosition;
    glm::vec4 m_controlPoint;
    glm::vec4 m_endPoint;
    float m_currentTime;

};

#endif // BEZIERCURVE_H
