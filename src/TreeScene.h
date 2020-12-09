#ifndef TREESCENE_H
#define TREESCENE_H
#include "shapes/Cylinder.h"
#include <iostream>
#include <string>
#include <memory.h>
#include <QGLWidget>
#include "glm/gtx/transform.hpp"
#include "ResourceLoader.h"
#include "gl/shaders/CS123Shader.h"
#include "SupportCanvas3D.h"
#include "ResourceLoader.h"
#include "Settings.h"
#include "Camera.h"
#include "OpenGLScene.h"

namespace CS123 { namespace GL {
    class VAO;
    class Shader;
    class CS123Shader;
    class Texture2D;
}}

// struct representing each cylinder for tree-building
struct Branch {
    glm::mat4x4 accumlatedMat; // transformation matrix for that particular branch. (accumulated view, translate, projection matrices)
    float angle;
};

class TreeScene {
    public: // public methods, global variables, constants here
        TreeScene(); // constructor
        ~TreeScene(); // destructor
        void draw();

        std::string axiom = "a"; // global variable representing the root node.(initialize as std::string)
        int maximumDepth = 5; // maximum recursion depth - global variable.
        std::vector<Branch> getPrimitiveList(); // returns the member variable (a vector of cylinders)

    protected:
        void setupTree(std::string inputStr, int width, int height, int numTree);
        void setupTreeAlternative(std::string inputStr, float rotationAngle);
        std::string generateStringAlt(std::string chars, int depth);
        void loadPhongShader();
        void setSceneUniforms(SupportCanvas3D *context);
        void render(SupportCanvas3D *context);

    private: // private member variables here
        void buildVAO();
        std::vector<GLfloat> m_vertexData;
        std::vector<Branch> m_branches; // vector that stores primitives and their transformation (composite matrix)
        std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
        std::unique_ptr<Cylinder> m_cylinder;
        std::string m_resultString;

        void generateNormals();
        void setAttribute(GLuint name, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type, bool normalize);
        std::vector<VBOAttribMarker> m_markers;     /// list of VBOAttribMarkers that describe how the data is laid out.
};

#endif // TREESCENE_H
