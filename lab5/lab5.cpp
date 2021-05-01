#include <iostream>
#include <vector>
#include "Stack.hpp"
using namespace std;


enum class MathOperator {
    plus, 
    minus,
    multiply, 
    divide,
    assign
};

enum class CompareOperator {
    equal,
    not_equal,
    more,
    more_or_equal,
    less,
    less_or_equal
};


enum class Type {
    Variable,
    Number,
    MathOperator,
    CompareOperator,
    Bracket,
    UNDEFINED
};


class ASTNode {
private:
    string data;
    Type type;
    ASTNode* left;
    ASTNode* right;
public:
    ASTNode();
    ~ASTNode();
};



int main() {
    ASTNode root;
    system("pause");
    return 0;
}



ASTNode::ASTNode()
{
    this->type = Type::UNDEFINED;
    this->data = "";
    this->left = nullptr;
    this->right = nullptr;
}

ASTNode::~ASTNode()
{
    delete left;
    delete right;
}