#ifndef TREESCENE_H
#define TREESCENE_H
#include "shapes/Cylinder.h"
#include <iostream>
#include <string>
#include <memory.h>
#include <QGLWidget>
#include "glm/gtx/transform.hpp"


namespace CS123 { namespace GL {
class VAO;
}}

// Stores the position and angle info needed when we encounter a '[' or ']'
struct position {
    glm::mat4x4 accMat;
    float angle;
};

// struct representing each cylinder for tree-building
struct Branch {
    Cylinder currBranch;
    glm::mat4x4 transformation; // transformation matrix for that particular branch. (accumulated view, translate, projection matrices)
    glm::vec3 position;
};

class TreeScene {
    public: // public methods, global variables, constants here
        TreeScene(); // constructor
        ~TreeScene(); // destructor
        void draw();

        std::string axiom = "A"; // global variable representing the root node.(initialize as std::string)
        int maximumDepth = 5; // maximum recursion depth - global variable.
        std::vector<Cylinder> getPrimitiveList(); // returns the member variable (a vector of cylinders)

    protected:
        void setupTree(std::string inputStr, int width, int height, int numTree);
        void setupTreeAlternative(std::string inputStr, float branchLength, float rotationAngle);
        std::string generateStringAlt(std::string chars, int depth);

    private: // private member variables here
        void buildVAO();
        std::vector<GLfloat> m_vertexData;
//        std::unique_ptr<CS123::GL::VAO> m_VAO;
       // std::vector<std::string> m_finalString; // will update (Ashley)
        std::vector<Branch> m_cylinders; // vector that stores primitives and their transformation (composite matrix)

};

#endif // TREESCENE_H
