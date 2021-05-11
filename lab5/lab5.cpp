#include <iostream>
#include <vector>
#include <string>
#include "Shunting-yard.hpp"
#include <fstream>
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

void InputData(vector<pair<string, double>> &variables);

int main(int argc, char* argv[]) {
    vector<pair<string, double>> variables;
    InputData(variables);
    system("pause");
    return 0;
}

void InputData(vector<pair<string, double>> &variables)
{
    ifstream input;
    input.open("input.txt");
    if (!input.is_open())
    {
        cout << "File cannot be openned" << endl;
        return;
    }
    while (!input.eof())
    {
        string str;
        getline(input, str);
        pair<string, double> curr;
        string temp;
        temp = str.substr(0, str.find('=') - 1);
        curr.first = temp;
        temp = str.substr(str.find('=')+2, str.size() - str.find('=') - 3);
        curr.second = stof(temp);
        variables.push_back(curr);
    }
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