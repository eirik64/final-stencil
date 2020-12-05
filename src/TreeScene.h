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
<<<<<<< HEAD
=======

// store startingVar as a char and convertedVar as a vector of chars,
//and just append to a final vector of chars as you replace your variables with the rules.
// = std::make_unique<char>({'A'})
>>>>>>> 782e9ddd62df9b9d7c41ec4a2203bbce15aa3ca6

class TreeScene {
    public: // public methods, global variables, constants here
        TreeScene(); // constructor
        ~TreeScene(); // destructor

<<<<<<< HEAD
        std::string axiom = "A"; // global variable representing the root node.(initialize as std::string)
        int maximumDepth = 5; // maximum depth global variable.
=======
        // SUGGESTION: Potentially initialize as an std::string???
        char axiom = 'A'; // global variable representing the root node.
>>>>>>> 782e9ddd62df9b9d7c41ec4a2203bbce15aa3ca6

    protected:
        void setupTree(std::string inputStr, int width, int height, int numTree);
        void setupTreeAlternative(std::string inputStr, float branchLength, float rotationAngle);
        std::string generateString(std::string chars);
        std::string generateStringAlt(std::string chars, int depth);

    private: // private member variables here
       // std::vector<std::string> m_finalString; // will update (Ashley)

};

#endif // TREESCENE_H
