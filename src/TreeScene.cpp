#include "TreeScene.h"
#include <iostream>
#include <string>

// Default constructor
TreeScene::TreeScene() {
    std::string firstGen = generateString(std::string("A")); // call generatestring on root node.
    std::string secondGen = generateString(firstGen);
    std::string thirdGen = generateString(secondGen); // produce strings over several generations to produce result strings..
    std::string fourthGen = generateString(thirdGen);
    // ... then use the resulting string to actually construct a tree.
    setupTree(fourthGen, 500, 500, 1); // initialize tree
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
void TreeScene::setupTree(std::string inputStr, int width, int height, int numTree) { // 'numTree' parameter might not be used
    // sets up the tree according to the final output string
    // Haven't figured out how to keep track of position of branch, how to geometrically construct the tree, etc...
    // also parameters are not finalized.. so feel free to propose a better structure!
    //
}

/* Takes in character, replaces all the axiom letters to a new set of alphabetic and special character collection
 * Input: an input string
 * Output: output string changed according to rule
 */
std::string TreeScene::generateString(std::string chars) {
    std::vector<char> finalVec;
    std::vector<char> v(chars.begin(), chars.end()); // use iterator to create a vector of characters
    for (int i=0; i < static_cast<int>(chars.size()); ++i) { // for every character in passed-in chars
        char current = v[i]; // i-th element in our new vector
        if (current == axiom) {
            finalVec.push_back('A');
            finalVec.push_back('+');
            finalVec.push_back('-');
            finalVec.push_back('[');
            finalVec.push_back('B');
            finalVec.push_back('+');
            finalVec.push_back('A');
            finalVec.push_back('-');
            finalVec.push_back('[');
            finalVec.push_back('B');
            finalVec.push_back(']');
            finalVec.push_back(']');
            finalVec.push_back('-');
            finalVec.push_back('[');
            finalVec.push_back('A');
            finalVec.push_back('B');
            finalVec.push_back(']'); // replace with the rule
        } else { // if it doesn't equal the axiom,
            finalVec.push_back(current); // we don't need to replace with anything.
        }
    }
    std::string outputString(finalVec.begin(), finalVec.end()); // convert to std string
    return outputString;
} // end of generateString() method
