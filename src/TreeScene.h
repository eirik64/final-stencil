#ifndef TREESCENE_H
#define TREESCENE_H
#include <iostream>
#include <string>
#include <memory.h>
#include <QGLWidget>

// rule 2
struct rule {
    // variables: A, B, +, -, [, ]
    // axiom: A
    // rule: A → A+-[B+A-[B]]-[AB]
    char startingVar = 'A';
    std::vector<char> convertedVar();
};
// store startingVar as a char and convertedVar as a vector of chars,
//and just append to a final vector of chars as you replace your variables with the rules.
// = std::make_unique<char>({'A'})

class TreeScene {
    public: // public methods, global variables, constants here
        TreeScene(); // constructor
        ~TreeScene(); // destructor
        char axiom = 'A'; // global variable representing the root node.

    protected:
        void setupTree(std::string inputStr, int width, int height, int numTree);
        std::string generateString(std::string chars);

    private: // private member variables here
       // std::vector<std::string> m_finalString; // will update (Ashley)

};

#endif // TREESCENE_H
