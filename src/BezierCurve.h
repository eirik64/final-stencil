#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "CamtransCamera.h"
#include "SupportCanvas3D.h"

#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>

class BezierCurve
{
public:
    BezierCurve(glm::vec4 position);
    ~BezierCurve();

    glm::vec4 PointOnCurve(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, float time);
    void moveCamera(CamtransCamera* camera, QWidget * canvas);

private:
    glm::vec4 m_startPosition;
    glm::vec4 m_controlPoint;
    glm::vec4 m_endPoint;


};

#endif // BEZIERCURVE_H
