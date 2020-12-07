#include "TreeScene.h"
#include <iostream>
#include <string>
#include "GL/glew.h"
#include "ResourceLoader.h"
#include "gl/shaders/CS123Shader.h"
using namespace CS123::GL;

// Default constructor
TreeScene::TreeScene()
{
//  std::string resultString = generateStringAlt(axiom, 1); // start by depth 1.
    m_cylinder = std::make_unique<Cylinder>(1, 15);
    //setupTreeAlternative(resultString, 1, 22.5); // initialize tree using the result string from the recursive method.
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

    // Using Flyweight pattern
//    for (int i = 0; i < (int) m_branches.size(); ++i) { // for every "branch" instance
       // m_phongShader->setUniform("m", glm::mat4x4(1)*glm::translate(glm::vec3(0,1,0))); // set uniforms
    std::unique_ptr<Cylinder> cylinder = std::make_unique<Cylinder>(1,15);
        cylinder->draw();
//    }

}

// This method will take in our generated string, the length of a branch that we generate,
// our overall rotational angle and our recursive depth
void TreeScene::setupTreeAlternative(std::string inputStr, float branchLength, float rotationAngle) {
    std::vector<position> stack; // Pushes in positions at '[' and Pops them at ']'

    for (int i = 0; i < (int)inputStr.length(); i++) {
        switch(inputStr[i]) {
            case 'a': {
                // do nothing
                break;
            }
            case 'b': { // draw a line at curr angle.
                // Draw line forward with the length of branchLength and update currentPos
                Branch newBranch;
                newBranch.transformation = glm::mat4x4(1)*glm::translate(glm::vec3(0,1,0)); // translate upward by height of the cylinder, 1
                newBranch.position = m_branches.back().position; // same position as before
                m_branches.push_back(newBranch); // push it to vector
                break;
            }
            case '[': {
                // Pushes position into stack, no drawing
                position newPos; // current position
                newPos.angle = m_branches.back().position.angle; // reset angle to current cylinder's pos angle.
                newPos.accMat = m_branches.back().transformation; // current transformation matrix
                stack.push_back(newPos);
                break;
            }
            case ']': { // there might be an overlap, but it would generally be fine i think
                // Pops latest position and continues drawing from that position
                position latestPos = stack.back(); // latest position = last element in the stack
                stack.pop_back(); // erase last element
                Branch newBranch;
                newBranch.position = latestPos;
                newBranch.transformation = glm::mat4x4(1);
                m_branches.push_back(newBranch); // push back with the updated, stored position (transforming current cylinder at hand)
                break;
            }
            case '+': { // Updates current position, angle decreases by 22.5 to signify turning left
                Branch newBranch;
                newBranch.position = m_branches.back().position; // update current position
                newBranch.transformation =glm::rotate(glm::mat4x4(1), -rotationAngle, glm::vec3(0,0,0)); // I think third parameter is wrong (rotation axis)
                break;
            }
            case '-': { // Updates current position, angle increases by 22.5 to signify turning right
                Branch newBranch;
                newBranch.position = m_branches.back().position; // update current position
                newBranch.transformation =glm::rotate(glm::mat4x4(1), rotationAngle, glm::vec3(0,0,0)); // I think third parameter is wrong (rotation axis)
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
    if (depth != maximumDepth) { // if not maximum depth,
        std::string resultString = generateStringAlt(outputString, depth + 1); // make a recursive call
        std::string outputString(resultString.begin(), resultString.end());
       // std::string outputString(v.begin(), v.end()); // again, convert to std::string
    }
    std::cout<<"output string: "<<outputString<<std::endl;
    return outputString;
}

