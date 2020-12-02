#include "TreeScene.h"
#include <iostream>
#include <string>

// Default constructor
TreeScene::TreeScene() {}


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
void TreeScene::setupTree(int width, int height, int numTree) {}

std::string TreeScene::generateString() {
    std::string initialSentence = axiom; // starting with axiom.
    std::string resultString;
    for (int i=0; i < initialSentence.length(); ++i) {
     //   std::string currentWord = initialSentence[i]
        // still working on this (splitting the character, and then creating a new string based on each character
        // will update this method. (Ashley)
    }
}
