#include "TreeScene.h"
#include <iostream>
#include <string>
#include "GL/glew.h"
using namespace CS123::GL;

// Default constructor
TreeScene::TreeScene()
{
      loadPhongShader();
      Branch root;
      root.accumlatedMat = glm::mat4x4(1.f);
      root.angle = 0;
      m_branches = std::vector<Branch>(); // initialization.
      m_branches.push_back(root);
      m_resultString = generateStringAlt(axiom, 1); // start by testing depth 1.
      setupTreeAlternative(m_resultString, 22.5); // initialize tree using the result string from the recursive method.
      m_cylinder = std::make_unique<Cylinder>(1, 15);
}


// Destructor
TreeScene::~TreeScene()
{
}

// VAO draw method
void TreeScene::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    std::cout<<"size of branches vector: "<< m_branches.size() <<std::endl;
    // Using Flyweight pattern
    for (int i = 0; i < (int) m_branches.size(); ++i) { // for every "branch" instance
        m_phongShader->setUniform("m", glm::mat4x4(1)*glm::translate(glm::vec3(0,1,0))); // set uniforms
        m_cylinder->draw();
    }
//    std::unique_ptr<Cylinder> cyl1 = std::make_unique<Cylinder>(1, 15);
//    cyl1->draw();
//    glm::translate(glm::translate(glm::vec3(0,1,0)), glm::vec3(0,1,0));

}

void TreeScene::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

// render() method
void TreeScene::render(SupportCanvas3D *context) {
//    setClearColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_phongShader->bind();
    setSceneUniforms(context);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_phongShader->unbind();

}

void TreeScene::generateNormals() {
    //generate random number between 0.0 and 1.0 for y
    int rand_int_y = rand();
    float rand_y = static_cast<float>(rand_int_y) / static_cast<float>(RAND_MAX);

    //generate random number between -1.0 and 1.0 for x and z
    int rand_int_x = rand();
    float rand_x = static_cast<float>(rand_int_x) / static_cast<float>(RAND_MAX);
    int rand_int_z = rand();
    float rand_z = static_cast<float>(rand_int_z) / static_cast<float>(RAND_MAX);

    //put x, y, z coordinates into VAO

    m_tree->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);

}

void TreeScene::setAttribute(GLuint name, GLuint numElementsPerVertex, int offset,
                               VBOAttribMarker::DATA_TYPE type, bool normalize) {
    m_markers.push_back(VBOAttribMarker(name, numElementsPerVertex, offset, type, normalize));
}

void TreeScene::setSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

//void TreeScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
//    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
//    shader->setUniform("v", context->getCamera()->getViewMatrix()); // set
//}

// This method will take in our generated string, the length of a branch that we generate,
// our overall rotational angle and our recursive depth
void TreeScene::setupTreeAlternative(std::string inputStr, float rotationAngle) {
    std::vector<glm::mat4x4> stack = std::vector<glm::mat4x4>();
    Branch current;
    current.accumlatedMat = glm::mat4x4(1.0f); // identity
    current.angle = 0; // Whatever initial angle would cause no change to the axiom when applied (assuming a 0 change in angles)

    for (int i = 0; i < (int)inputStr.length(); i++) {
        std::cout << i << std::endl;
        switch(inputStr[i]) {
            case 'a': {
                // do nothing
                break;
            }
            case 'b': { // draw a line at curr angle.
                // Draw line forward with the length of branchLength and update currentPos
                Branch newBranch;
                // NOTE: Might have to change our angl to radians when we use glm::rotate but IDK!!! Just a thought

                // IMPORTANT: This next line is the meat of the code. If our tree comes out wrong it probably has to do with what we are multipying with and how!!!
                newBranch.accumlatedMat = current.accumlatedMat*glm::translate(glm::vec3(0.f,1.f,0.f)) * glm::rotate(current.angle, glm::vec3(0.f, 1.f, 0.f)) * glm::mat4x4(1.f); // translate upward by height of the cylinder, 1
                current.accumlatedMat = newBranch.accumlatedMat;
                newBranch.angle = 0; // same position as before so we reset angle back to 0
                current.angle = 0;
                std::cout << "hllo" << std::endl;
                m_branches.push_back(newBranch); // push it to vector
                break;
            }
            case '[': {
                // Pushes position into stack, no drawing
                /*position newPos; // current position
                newPos.angle = m_branches.back().position.angle; // reset angle to current cylinder's pos angle.
                newPos.rotate = m_branches.back().position.rotate;*/ // current transformation matrix
                stack.push_back(current.accumlatedMat);
                break;
            }
            case ']': { // there might be an overlap, but it would generally be fine i think
                // Pops latest position and continues drawing from that position
                current.accumlatedMat = stack.back(); // latest position = last element in the stack
                stack.pop_back(); // erase last element
                //This is all we should have to do!
//                Branch newBranch;
//                newBranch.position = latestPos;
//                newBranch.accumlatedMat = glm::mat4x4(1);
//                m_branches.push_back(newBranch); // push back with the updated, stored position (transforming current cylinder at hand)
                break;
            }
            case '+': { // Updates current position, angle decreases by 22.5 to signify turning left
                current.angle -= rotationAngle; // For now wee hold onto the new angle in current. Apply it to the accumulation matrix once we reeach a call to draw forward!

                //Hold off on applying the transformation because it'll be done in switch case 'b' anyways!!
                //current.accumlatedMat = glm::rotate(-rotationAngle, glm::vec3(0.f,1.f,0.f)) * glm::mat4x4(1.f); // I think third parameter is wrong (rotation axis)

                break;
            }
            case '-': { // Updates current position, angle increases by 22.5 to signify turning right
                current.angle += rotationAngle;
                //current.accumlatedMat =glm::rotate(rotationAngle, glm::vec3(0,1.f,0)) * glm::mat4x4(1.f); // I think third parameter is wrong (rotation axis)
                break;
            }
        }
    }
}

/*
*/
std::string TreeScene::generateStringAlt(std::string chars, int depth) {
    std::vector<char> intermedVec;
    std::vector<char> v(chars.begin(), chars.end());
    std::cout << chars << std::endl;

    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < (int) v.size(); j++) {
            char current = v[i];
            // B -> BB+[-B+B+B+B]-[B+B-B]
            switch (current) {
            case 'b':
                intermedVec.push_back('b');
                intermedVec.push_back('b');
                intermedVec.push_back('+');
                intermedVec.push_back('[');
                intermedVec.push_back('-');
                intermedVec.push_back('b');
                intermedVec.push_back('+');
                intermedVec.push_back('b');
                intermedVec.push_back('+');
                intermedVec.push_back('b');
                intermedVec.push_back('+');
                intermedVec.push_back('b');
                intermedVec.push_back(']');
                intermedVec.push_back('-');
                intermedVec.push_back('[');
                intermedVec.push_back('b');
                intermedVec.push_back('+');
                intermedVec.push_back('b');
                intermedVec.push_back('-');
                intermedVec.push_back('b');
                intermedVec.push_back(']');
                break;
            // A -> B-[[A]+++A]B[+BA]-A
            case 'a':
                intermedVec.push_back('b');
                intermedVec.push_back('-');
                intermedVec.push_back('[');
                intermedVec.push_back('[');
                intermedVec.push_back('a');
                intermedVec.push_back(']');
                intermedVec.push_back('+');
                intermedVec.push_back('+');
                intermedVec.push_back('+');
                intermedVec.push_back('a');
                intermedVec.push_back(']');
                intermedVec.push_back('b');
                intermedVec.push_back('[');
                intermedVec.push_back('+');
                intermedVec.push_back('b');
                intermedVec.push_back('a');
                intermedVec.push_back(']');
                intermedVec.push_back('-');
                intermedVec.push_back('a');
                break;
            default:
                intermedVec.push_back(current);
            }
        }
        v = intermedVec;
        intermedVec.clear();
    } // end of double for loop

    std::string outputString(v.begin(), v.end()); // convert to std string

    return outputString;
}

