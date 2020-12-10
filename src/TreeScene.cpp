#include "TreeScene.h"
#include <iostream>
#include <string>
#include "GL/glew.h"
#include "labs/lab05/cs123_lib/resourceloader.h"
#include "labs/lab05/cs123_lib/errorchecker.h"
#include "gl/shaders/ShaderAttribLocations.h"
using namespace CS123::GL;

// Default constructor
TreeScene::TreeScene() : m_numRows(100), m_numCols(m_numRows)
{
      loadPhongShader();
      Branch root;
      root.accumlatedMat = glm::mat4x4(1.f);
      root.angle = 0;
      m_branches = std::vector<Branch>(); // initialization.
      m_branches.push_back(root);
      m_resultString = generateStringAlt(axiom, 1); // start by testing depth 1.
      std::cout<<"result string: "<<m_resultString<<std::endl;
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
        m_phongShader->setUniform("m", m_branches[i].accumlatedMat); // set uniforms
        std::cout<<"WhatUp!"<<std::endl;
        m_cylinder->draw();
    }

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

 //   m_tree->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);

}

//void TreeScene::setAttribute(GLuint name, GLuint numElementsPerVertex, int offset,
//                               VBOAttribMarker::DATA_TYPE type, bool normalize) {
//    m_markers.push_back(VBOAttribMarker(name, numElementsPerVertex, offset, type, normalize));
//}

void TreeScene::setSceneUniforms(SupportCanvas3D *context) {
    Camera *camera = context->getCamera();
    m_phongShader->setUniform("useLighting", settings.useLighting);
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->setUniform("p" , camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getViewMatrix());
}

void TreeScene::setMatrixUniforms(Shader *shader, SupportCanvas3D *context) {
    shader->setUniform("p", context->getCamera()->getProjectionMatrix());
    shader->setUniform("v", context->getCamera()->getViewMatrix()); // set
}

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
                rotationAngle = glm::radians(rotationAngle);

                // IMPORTANT: This next line is the meat of the code. If our tree comes out wrong it probably has to do with what we are multipying with and how!!!
                newBranch.accumlatedMat = current.accumlatedMat*glm::translate(glm::vec3(0.f,1.f,0.f)) * glm::rotate(current.angle, glm::vec3(1.f, 0.f, 1.f)); // translate upward by height of the cylinder, 1
                current.accumlatedMat = newBranch.accumlatedMat;
                newBranch.angle = 0; // same position as before so we reset angle back to 0
                current.angle = 0;
                m_branches.push_back(newBranch); // push it to vector
                break;
            }
            case '[': {
                // Pushes position into stack, no drawing
                stack.push_back(current.accumlatedMat);
//                Branch newBranch;
//                newBranch.accumlatedMat = current.accumlatedMat;
//                m_branches.push_back(newBranch);
                break;
            }
            case ']': { // there might be an overlap, but it would generally be fine i think
                // Pops latest position and continues drawing from that position
                current.accumlatedMat = stack.back(); // latest position = last element in the stack
                stack.pop_back(); // erase last element
                break;
            }
            case '+': { // Updates current position, angle decreases by 22.5 to signify turning left
            Branch newBranch;
                current.angle -= rotationAngle;
//                current.angle -= rotationAngle; // For now wee hold onto the new angle in current. Apply it to the accumulation matrix once we reeach a call to draw forward!
//                newBranch.accumlatedMat = current.accumlatedMat*glm::translate(glm::vec3(0.f,1.f,0.f))
//                        * glm::rotate(current.angle, glm::vec3(1.f, 0.f, 1.f)); // translate upward by height of the cylinder, 1
//                current.accumlatedMat = newBranch.accumlatedMat;
//                newBranch.angle = 0; // same position as before so we reset angle back to 0
//                m_branches.push_back(newBranch); // push it to vector
//                stack.push_back(current.accumlatedMat);
                //Hold off on applying the transformation because it'll be done in switch case 'b' anyways!!
                break;
            }
            case '-': { // Updates current position, angle increases by 22.5 to signify turning right
//                Branch newBranch;
                current.angle += rotationAngle;
//                current.angle += rotationAngle; // For now wee hold onto the new angle in current. Apply it to the accumulation matrix once we reeach a call to draw forward!
//                newBranch.accumlatedMat = current.accumlatedMat*glm::translate(glm::vec3(0.f,1.f,0.f))
//                        * glm::rotate(current.angle, glm::vec3(1.f, 0.f, 1.f)); // translate upward by height of the cylinder, 1
//                current.accumlatedMat = newBranch.accumlatedMat;
//                newBranch.angle = 0; // same position as before so we reset angle back to 0
//                m_branches.push_back(newBranch); // push it to vector
//                stack.push_back(current.accumlatedMat);
                break;
            }
        }
    }
}

/*
*/
std::string TreeScene::generateStringAlt(std::string chars, int depth) {
    std::string intermedString; // intermediate string for in-place implementation
    std::vector<char> outputCharVec(chars.begin(), chars.end());
    std::vector<char> intermedVec = outputCharVec;

    for (int i = 0; i < depth; i++) {

        for (int j = 0; j < (int) outputCharVec.size(); j++) {
            char current = outputCharVec[i];
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
        outputCharVec = intermedVec; // set the output vector to the intermediate vector.
        intermedVec.clear();
        std::cout<<"How many times does this print"<<std::endl;
    } // end of double for loop

    std::string outputString(outputCharVec.begin(), outputCharVec.end()); // final output string

    return outputString;
}

// IMPLEMENT ENVIRONMENTAL MAPPING!


// IMPLEMENT TERRAIN!
// Note: currently, m_shape (terrain VAO) is causing some errors. Would appreciate if you can take a look at it!
// Also, TA mentioned that they don't run our projects but instead they grade just on the spot on the demo day.
// So it's more important to make our project look finished and polished, hence why the terrain and environmental mapping
//

/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and column.
 */
float TreeScene::randValue(int row, int col) {
    return -1.0 + 2.0 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
}


/**
 * Returns the object-space position for the terrain vertex at the given row and column.
 */
glm::vec3 TreeScene::getPosition(int row, int col) {
    glm::vec3 position;
    position.x = 10 * row/m_numRows - 5;
    position.y = 0;
    position.z = 10 * col/m_numCols - 5;

    float scale = 20.f;

    // TODO: Adjust position.y using value noise.
    for (int i=0; i < 3; ++i, scale/= 2) { // operation: "every time i changes, divide scale by 2"
        int new_row = floor(row/scale); // ensure floating point division
        int new_col = floor(col/scale);
        float row_fract = glm::fract(row/scale); // getting exact current row and column (of current point we want to interpolate)
        float col_fract = glm::fract(col/scale);

        // get nearest height (Task 3)
        float A = randValue(new_row, new_col); // left upper corner
        float B = randValue(new_row, new_col + 1); // right upper corner
        float C = randValue(new_row + 1, new_col); // left lower corner
        float D = randValue(new_row + 1, new_col + 1); // right lower corner
        // get four heights

        // big frequency
        float interpolate_A_and_B = glm::mix(A, B, col_fract*col_fract*(3-2*col_fract));// Interpolate between A and B (points)
        float interpolate_C_and_D = glm::mix(C, D, col_fract*col_fract*(3-2*col_fract));// Interpolate between C and D (points)

        // medium frequency

        float interpolate_AB_CD = glm::mix(interpolate_A_and_B,
                                            interpolate_C_and_D,
                                            row_fract*row_fract*(3-2*row_fract)); // Interpolate vertically
        position.y += interpolate_AB_CD/pow(2, i); // set position y to the new interpolated location.

    } // end of for loop
    return position;
}


/**
 * Returns the normal vector for the terrain vertex at the given row and column.
 */
glm::vec3 TreeScene::getNormal(int row, int col) {
    // TODO: Compute the normal at the given row and column using the positions of the
    //       neighboring vertices.
    glm::vec3 curr_position_vector = getPosition(row, col); // vector of current point.

    int startIndex_row = row - 1; // loop conditions
    int endIndex_row = row + 1;

    int startIndex_col = col - 1;
    int endIndex_col = col + 1;
    glm::vec3 normalized_vector;

    std::vector<glm::vec3> neighbors = {getPosition(row -1, col),
                                        getPosition(row-1, col +1),
                                       getPosition(row, col + 1),
                                       getPosition(row+1, col + 1),
                                       getPosition(row+1, col),
                                       getPosition(row+1, col - 1),
                                       getPosition(row, col - 1),
                                       getPosition(row-1, col - 1),
                                        getPosition(row -1, col)};

    for (int i=0; i < neighbors.size()-1; ++i) {
         glm::vec3 curr_neighbor_position_vector = neighbors[i]; // vector of neighboring point.
          glm::vec3 next_neighbor_position_vector = neighbors[i+1]; // vector of neighboring point.

         glm::vec3 vector_from_center_to_neighbor = curr_neighbor_position_vector - curr_position_vector;
         glm::vec3 vector_to_next_neighbor = next_neighbor_position_vector - curr_position_vector;

         glm::vec3 cross_product = glm::cross(vector_from_center_to_neighbor , vector_to_next_neighbor);
         normalized_vector += glm::normalize(cross_product);
    }

    normalized_vector = glm::normalize(normalized_vector); // average. (there are 8 neighboring pixels)

    return normalized_vector;
}


void TreeScene::init() {
    // TODO: Change from GL_LINE to GL_FILL in order to render full triangles instead of wireframe.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // changing last argument to
    // switch view from wireframe to shaded


    // Initializes a grid of vertices using triangle strips.
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
    std::vector<glm::vec3> data(2 * numVertices);
    int index = 0;
    for (int row = 0; row < m_numRows - 1; row++) {
        for (int col = m_numCols - 1; col >= 0; col--) {
            data[index++] = getPosition(row, col);
            data[index++] = getNormal  (row, col);
            data[index++] = getPosition(row + 1, col);
            data[index++] = getNormal  (row + 1, col);
        }
        data[index++] = getPosition(row + 1, 0);
        data[index++] = getNormal  (row + 1, 0);
        data[index++] = getPosition(row + 1, m_numCols - 1);
        data[index++] = getNormal  (row + 1, m_numCols - 1);
    }

    // Initialize OpenGLShape.
//    m_shape = std::make_unique<OpenGLShape>();
//    std::cout<<"Is this method called?"<<std::endl;
//    m_shape->setVertexData(&data[0][0], data.size() * 3, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, numVertices);
//    m_shape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
//    m_shape->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);
//    m_shape->buildVAO();
}


/**
 * Draws the terrain.
 */
void TreeScene::terrainDraw()
{
//    m_shape->draw();
}


