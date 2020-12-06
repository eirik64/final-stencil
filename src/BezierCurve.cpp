#include "BezierCurve.h"



BezierCurve::BezierCurve(Camera camera):
    m_camera(camera),
    m_startPosition(camera.getPosition()),
    m_controlPoint(glm::vec4(0.f, 0.f, 4.f, 1.f)),
    m_endPoint(glm::vec4(2.f, 0.f, 0.f, 1.f)),
    m_currentTime(0.f)
{

}

glm::vec4 BezierCurve::PointOnCurve(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, float time) {

    /* Quadratic Curve

      L1(t) = (1-t)*P1 + t*P2
      L2(t) = (1-t)*P2 + t*P3
      Q(t) = (1-t)*L1(t) + t*L2(t)
      OR
      Q(t) = P1 + (1-t)^2(P0-P1) + t^2(P2 - P1)

      */
    // so as not to keep recomputing these
    float tMinusOne =  (1.f - time);

    // Computing L1(t) && L2(t)
    glm::vec4 l1 = tMinusOne * p1 + time * p2;
    glm::vec4 l2 = tMinusOne * p2 + time * p3;

    glm::vec4 q = tMinusOne * l1 + time * l2;

    return q;
}

void BezierCurve::moveCamera() {
    // initialize a vec4 to hold our points
    glm::vec4 vPoint = glm::vec4{0.f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(1.5f);

    // To help visualize the curve
    glBegin(GL_LINE_STRIP);

    for (float t = 0; t < 1.f + (1.f/25.f); t += (1.f/ 25.f)) {
        vPoint = PointOnCurve(m_startPosition, m_controlPoint, m_endPoint, t);
        glVertex3f(vPoint.x, vPoint.y, vPoint.z);
    }
    glEnd();

    for (float t = 0; t < 1.f -.0001f; t += (1.f/ 100.f)) {
        vPoint = PointOnCurve(m_startPosition, m_controlPoint, m_endPoint, m_currentTime);
        m_camera.updatePosition(vPoint.x, vPoint.y, vPoint.z);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

}
