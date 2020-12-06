#include "TreeScene.h"
#include <iostream>
#include <string>


// Default constructor
TreeScene::TreeScene()
{
//    std::string resultString = generateStringAlt(axiom, 1); // start by depth 1.
//    m_cylinders = {};

    //setupTreeAlternative(resultString, 1, 22.5); // initialize tree using the result string from the recursive method.
    // branch length = 1 (using unit cylinder from shapes).
}


// Destructor
TreeScene::~TreeScene()
{
}

/*
 *  Method to initiate the tree.
 *  Input parameters: width (int), height(int), and number of trees in the scene.
 *  Width and heights will essentially be width and height of the cylinder
 *  forming the main bark of the tree.
 *  Function: parses the string generated from the l-system rules
 *  and generates the tree.
 */
//void TreeScene::setupTree(std::string inputStr, int width, int height, int numTree) {
//    // sets up the tree according to the final output string

//}

//std::vector<Cylinder> TreeScene::getPrimitiveList() {
//    return m_cylinders;
//}

// VAO draw method
void TreeScene::draw() {
    std::make_unique<Cylinder>(1, 15)->draw();
//    if (m_VAO) {
//        m_VAO->bind();
//        m_VAO->draw();
//        m_VAO->unbind();
//    }
}

// build VAO
void TreeScene::buildVAO() {
//    const int numFloatsPerVertex = 6;
//    const int numVertices = m_vertexData.size() / numFloatsPerVertex;

//    std::vector<VBOAttribMarker> markers;
//    markers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
//    markers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 3*sizeof(float)));
//    VBO vbo = VBO(m_vertexData.data(), m_vertexData.size(), markers);
//    m_VAO = std::make_unique<VAO>(vbo, numVertices);
}

// This method will take in our generated string, the length of a branch that we generate,
// our overall rotational angle and our recursive depth

// we will modify m_cylinders, push each cylinder to the vector,
void TreeScene::setupTreeAlternative(std::string inputStr, float branchLength, float rotationAngle) {
    std::vector<position> stack; // Pushes in positions at '[' and Pops them at ']'

    for (int i = 0; i < (int)inputStr.length(); i++) {
        switch(inputStr[i]) {
            case 'a': {
                // do nothing
                break;
            }
            case 'b': { // draw a line at curr angle.

                const Cylinder cylinder = Cylinder(1,15); // initialize new cylinder
//                std::unique_ptr<Cylinder> cylinder = std::make_unique<Cylinder>(1, 15);
                Branch newBranch;
                newBranch.currBranch = cylinder;
                newBranch.transformation = glm::mat4x4(1)*glm::translate(glm::vec3(0,1,0)); // translate upward by height of the cylinder, 1
                m_cylinders.push_back(newBranch); // push it into


//                if (m_cylinders.size() == 0) { // when it's the first branch to be added to the list of cylinders
//                 //   newBranch.currBranch = std::make_unique<Cylinder>(1, 15);
//                    newBranch.transformation = glm::mat4x4(1); // Identity matrix
//                    newBranch.position = glm::vec3(0,0,0); // have to set the initial position.
//                } else {
//              //      newBranch.currBranch = std::make_unique<Cylinder>(1, 15);
//                    newBranch.transformation = glm::mat4x4(1); // Identity matrix, equiv. to the step of "doing nothing"
//                    newBranch.position = m_cylinders[m_cylinders.size()-1].position + glm::vec3(0,1,0); // just increase in y-direction according to cylinder height (1, in this case)
//                }
//                m_cylinders.push_back(newBranch); // push back the new branch
//                // Draw line forward with the length of branchLength and update currentPos
                break;
            }
            case '[': {
                // Pushes position into stack, no drawing

                break;
            }
            case ']': {
                // Pops latest position and continues drawing from that position
                break;
            }
//            case '+': {
//                // Updates current position, angle decreases by 22.5 to signify turning left
//            Branch newBranch; // param1 = 1, param2 = 15
//            if (m_cylinders.size() == 0) { // when it's the first branch to be added to the list of cylinders
////                newBranch.currBranch = std::make_unique<Cylinder>(1, 15);
////                newBranch.transformation = glm::rotate(glm::mat4x4(1), rotationAngle); // rotation 22.5 degrees
//               // glm::rotate(compositeMat, transform->angle, transform->rotate)
//                newBranch.position = glm::vec3(0,0,0); // have to set the initial position.
//            } else {

////                newBranch.currBranch = std::make_unique<Cylinder>(1, 15);
////                newBranch.transformation = glm::rotate(glm::mat4x4(1), rotationAngle); // Identity matrix, equiv. to the step of "doing nothing"
////                newBranch.position = m_cylinders[m_cylinders.size()-1].position + glm::vec3(0,1,0); // just increase in y-direction according to cylinder height (1, in this case)
//            }
//            m_cylinders.push_back(newBranch); // push back the new branch
//                break;
//            }
//            case '-': {
//                // Updates current position, angle increases by 22.5 to signify turning right
//                break;
//            }
        }
    }
}

/*
*/
std::string TreeScene::generateStringAlt(std::string chars, int depth) {
//    std::vector<char> intermedVec;
//    std::vector<char> v(chars.begin(), chars.end());

//    for (int i = 0; i < depth; i++) {
//        for (int j = 0; j < (int) v.size(); j++) {
//            char current = v[i];
//            // B -> BB+[-B+B+B+B]-[B+B-B]
//            switch (current) {
//            case 'b':
//                intermedVec.push_back('b');
//                intermedVec.push_back('b');
//                intermedVec.push_back('+');
//                intermedVec.push_back('[');
//                intermedVec.push_back('-');
//                intermedVec.push_back('b');
//                intermedVec.push_back('+');
//                intermedVec.push_back('b');
//                intermedVec.push_back('+');
//                intermedVec.push_back('b');
//                intermedVec.push_back('+');
//                intermedVec.push_back('b');
//                intermedVec.push_back(']');
//                intermedVec.push_back('-');
//                intermedVec.push_back('[');
//                intermedVec.push_back('b');
//                intermedVec.push_back('+');
//                intermedVec.push_back('b');
//                intermedVec.push_back('-');
//                intermedVec.push_back('b');
//                intermedVec.push_back(']');
//                break;
//            // A -> B-[[A]+++A]B[+BA]-A
//            case 'a':
//                intermedVec.push_back('b');
//                intermedVec.push_back('-');
//                intermedVec.push_back('[');
//                intermedVec.push_back('[');
//                intermedVec.push_back('a');
//                intermedVec.push_back(']');
//                intermedVec.push_back('+');
//                intermedVec.push_back('+');
//                intermedVec.push_back('+');
//                intermedVec.push_back('a');
//                intermedVec.push_back(']');
//                intermedVec.push_back('b');
//                intermedVec.push_back('[');
//                intermedVec.push_back('+');
//                intermedVec.push_back('b');
//                intermedVec.push_back('a');
//                intermedVec.push_back(']');
//                intermedVec.push_back('-');
//                intermedVec.push_back('a');
//                break;
//            default:
//                intermedVec.push_back(current);
//            }
//        }
//        v = intermedVec;
//        intermedVec.clear();
//    } // end of double for loop

//    std::string outputString(v.begin(), v.end()); // convert to std string
//    if (depth != maximumDepth) { // if not maximum depth,
//        std::string resultString = generateStringAlt(outputString, depth + 1); // make a recursive call
//        std::string outputString(resultString.begin(), resultString.end());
//       // std::string outputString(v.begin(), v.end()); // again, convert to std::string
//    }
//    std::cout<<"output string: "<<outputString<<std::endl;
//    return outputString;
}

