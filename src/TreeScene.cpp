#include "TreeScene.h"
#include <iostream>
#include <string>

// Default constructor
TreeScene::TreeScene() {
    std::string resultString = generateStringAlt(axiom, 1); // start by depth 1.
    setupTree(resultString, 500, 500, 1); // initialize tree using the result string from the recursive method.
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

// ERICK: I don't want to delete anything so I'll just kinda add stuff and we can sift through this afterwwards

// This method will take in our generated string, the length of a branch that we generate,
// our overall rotational angle and our recursive depth
void TreeScene::setupTreeAlternative(std::string inputStr, float branchLength, float rotationAngle) {
    std::vector<position> stack; // Pushes in positions at '[' and Pops them at ']'
    // Current position as I go through the inputStr
    position currentPos;
    for (int i = 0; i < (int)inputStr.length(); i++) {
        switch(inputStr[i]) {
        case 'a':
            // Do nothing
            break;
        case 'b':
            // Draw line forward with the length of branchLength and update currentPos
            break;
        case '[':
            // Pushes position into stack, no drawing
            break;
        case ']':
            // Pops latest position and continues drawing from that position
            break;
        case '+':
            // Updates current position, angle decreases by 22.5 to signify turning left
            break;
        case '-':
            // Updates current position, angle increases by 22.5 to signify turning right
            break;
<<<<<<< HEAD
=======
        }
    }
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
>>>>>>> 782e9ddd62df9b9d7c41ec4a2203bbce15aa3ca6
        }
    }
}

// Ashley : Deleted my version of generateString but I am keeping it separately in another file just in case.

/*
˙∆˚ I like this face
I looked over your code. (Ashley)
Axiom is indeed one character long!
Depth is a good idea, since we need to indicate how many times we want to recursively call this method.
Using the rules for the very last tree in the google doc
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
                intermedVec.push_back(']'); // This looks correct, based on our rules!
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
                intermedVec.push_back('a'); // This looks correct also.
                break;
            default:
                intermedVec.push_back(current);
            }
        }
        v = intermedVec;
        intermedVec.clear();
    } // end of double for loop

    std::string outputString(v.begin(), v.end()); // convert to std string
    if (depth != maximumDepth) {
        std::string resultString = generateStringAlt(outputString, depth + 1); // make a recursive call
        std::string outputString(resultString.begin(), resultString.end());
       // std::string outputString(v.begin(), v.end()); // again, convert to std::string
    }
    std::cout<<"output string: "<<outputString<<std::endl;
    return outputString;
<<<<<<< HEAD
}

=======
} // end of generateString() method


/*
Please look over my code here. I'm supeer exhausteed by this point so this isn't really processing
for me anymore. Feel free to change anything that may not make sense or scrap it. I'm going to sleep now ˙∆˚
I'm assuming here that our axiom is just one character long... I hope
Also, I included depth to represent the amount of times we went to walk
through our string and update it based on our rules.
I'm using the rules for the very last tree that I added in the docs. Subject to change**
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

    }
    std::string outputString(v.begin(), v.end()); // convert to std string
    return outputString;
}


>>>>>>> 782e9ddd62df9b9d7c41ec4a2203bbce15aa3ca6
