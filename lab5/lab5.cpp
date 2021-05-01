#include <iostream>
#include <vector>

using namespace std;


enum class Type {
    variable,
    constant,
    math_operator,
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