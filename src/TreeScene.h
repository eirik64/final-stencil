#ifndef TREESCENE_H
#define TREESCENE_H
#include <iostream>
#include <string>

// rule 2
struct rule {
    // variables: A, B, +, -, [, ]
    // axiom: A
    // rule: A → A+-[B+A-[B]]-[AB]
    std::string startingVar = "A";
    std::string convertedVar = "A+-[B+A-[B]]-[AB]"; // will update this. (Ashley)
};

class TreeScene {
    public: // public methods, global variables, constants here
        TreeScene(); // constructor
        ~TreeScene(); // destructor
        std::string axiom = "A"; // global variable representing the root node.

    protected:
        void setupTree(int width, int height, int numTree);
        std::string generateString();

    private: // private member variables here
       // std::vector<std::string> m_finalString; // will update (Ashley)

};

#endif // TREESCENE_H
