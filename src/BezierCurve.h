#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "CamtransCamera.h"
#include "SupportCanvas3D.h"
#include "Settings.h"

#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <QElapsedTimer>
#include <QTimer>
#include <QDebug>

class BezierCurve
{
public:
    BezierCurve();
    ~BezierCurve();

    glm::vec4 PointOnCurve(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, float time);
    void moveCamera(CamtransCamera* camera, SupportCanvas3D * canvas, PathType path);


private:
    glm::vec4 m_startPosition;
    glm::vec4 m_controlPoint;
    glm::vec4 m_endPoint;
    QElapsedTimer m_timeElapsed;



};

#endif // BEZIERCURVE_H
