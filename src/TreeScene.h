#ifndef TREESCENE_H
#define TREESCENE_H
#include <iostream>
#include <string>
#include <memory.h>
#include <QGLWidget>

// struct representing rule
// store startingVar as a char and convertedVar as a vector of chars,
// and just append to a final vector of chars as you replace your variables with the rules.
struct rule {
    char startingVar = 'A';
    std::vector<char> convertedVar();
};

// Stores the position and angle info needed when we encounter a '[' or ']'
struct position {
    float pos;
    float angle;
};

class TreeScene {
    public: // public methods, global variables, constants here
        TreeScene(); // constructor
        ~TreeScene(); // destructor

        std::string axiom = "A"; // global variable representing the root node.(initialize as std::string)
        int maximumDepth = 5; // maximum depth global variable.

    protected:
        void setupTree(std::string inputStr, int width, int height, int numTree);
        void setupTreeAlternative(std::string inputStr, float branchLength, float rotationAngle);
        std::string generateString(std::string chars);
        std::string generateStringAlt(std::string chars, int depth);

    private: // private member variables here
       // std::vector<std::string> m_finalString; // will update (Ashley)

};

#endif // TREESCENE_H
