#include "BezierCurve.h"



BezierCurve::BezierCurve()
{
    //m_timeElapsed = new QElapsedTimer();
    m_timeElapsed.start();
}

BezierCurve::~BezierCurve() {

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

void BezierCurve::moveCamera(CamtransCamera *camera, SupportCanvas3D *canvas, PathType path) {
    // initialize a vec4 to hold our points
    glm::vec4 vPoint = glm::vec4{0.f};
    glm::vec4 look;
    glm::vec4 up = glm::vec4(0.f, 1.f, 0.f, 0.f);
    bool onPath;
    float prevT = 0.f;

    switch (path) {
    case PATH_ONE:
        m_startPosition = glm::vec4(2.f, 2.f, 2.f, 1.f);
        m_controlPoint = glm::vec4(0.f, 3.f, 3.f, 1.f);
        m_endPoint = glm::vec4(-2.f, 2.f, 2.f, 1.f);
        onPath = true;
        break;
    case PATH_TWO:
        m_startPosition = glm::vec4(8.f, 5.f, 8.f, 1.f);
        m_controlPoint = glm::vec4(0.f,6.5f, 10.f, 1.f);
        m_endPoint = glm::vec4(-8.f, 5.f, 8.f, 1.f);
        onPath = true;
        break;
    case PATH_THREE:
        m_startPosition = glm::vec4(0.f, 0.f, 8.f, 1.f);
        m_controlPoint = glm::vec4(-7.f, 5.f, 0.f, 1.f);
        m_endPoint = glm::vec4(0.f, 10.f, -8.f, 1.f);
        onPath = true;
        break;
    case PATH_NONE:
        onPath = false;
        break;
    case NUM_PATH_TYPES:
        onPath = false;
        break;
    }
    //while (onPath) {
//        for (float t = 0; t < 1.f +.0001f; t += (1.f/ 100.f)) {
//            vPoint = PointOnCurve(m_startPosition, m_controlPoint, m_endPoint, t);
//            look = glm::vec4(0.f) - vPoint;

//            //std::cout << m_timeElapsed.elapsed() << std::endl;
//            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            qDebug() << m_timeElapsed.elapsed();
//            if (m_timeElapsed.elapsed() > 10000)  {
//                std::cout << "Hey" << std::endl;
//                m_timeElapsed.restart();
//                camera->orientLook(vPoint, look, up);
//                canvas->update();
//            }
    while (prevT < 1.0f + .0001f) {
        if (m_timeElapsed.elapsed() > 100) {

            prevT += (1.f/ 100.f);
            std::cout << m_timeElapsed.elapsed()  << " " << prevT << std::endl;
            vPoint = PointOnCurve(m_startPosition, m_controlPoint, m_endPoint, prevT);
            look = glm::vec4(0.f) - vPoint;
            camera->orientLook(vPoint, look, up);
            m_timeElapsed.restart();
            canvas->updateGL();
        }
    }

//            //std::cout << t << " "<<vPoint.x<<" "<< vPoint.y << " " << vPoint.z << std::endl;
//        }



        // Other side of the curve
//        for (float t = 0; t < 1.f +.0001f; t += (1.f/ 100.f)) {
//            vPoint = PointOnCurve(m_endPoint, -m_controlPoint, m_startPosition, t);
//            look = glm::vec4(0.f) - vPoint;
//            camera->orientLook(vPoint, look, up);

//            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            canvas->update();
//            //std::cout << t << " "<<vPoint.x<<" "<< vPoint.y << " " << vPoint.z << std::endl;
//        }

    //}

}
