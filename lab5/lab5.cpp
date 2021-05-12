#include <iostream>
#include <vector>
#include <string>
#include "Shunting-yard.hpp"
#include <fstream>
#include <map>
#include <utility>
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
    vector<ASTNode*> children;
public:
    ASTNode();
    void AddChild(string data);
    ASTNode* getNewNode(string data);
    void PrintChildren(ASTNode node);
};

void InputData(map<string, double>& variables, string& problem);

int main(int argc, char* argv[]) {
    map<string, double> variables;
    string problem;
    ASTNode node;
    node.AddChild("+");
    node.AddChild("-");
    node.AddChild("/");
    node.PrintChildren(node);
    InputData(variables, problem);
    system("pause");
    return 0;
}

void InputData(map<string, double> &variables, string& problem)
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
        if (!(str.find('*') != -1 || str.find('-') != -1 || str.find('+') != -1 || str.find('^') != -1 || str.find('/') != -1))
        {
            pair<string, double> curr;
            string temp;
            temp = str.substr(0, str.find('=') - 1);
            curr.first = temp;
            temp = str.substr(str.find('=') + 2, str.size() - str.find('=') - 3);
            curr.second = stof(temp);
            variables.insert(curr);
        }
        else
        {
            problem = str.substr(0, str.size() - 1);
        }
    }
    input.close();
}


ASTNode::ASTNode()
{
    this->type = Type::UNDEFINED;
    this->data = "";
}

void ASTNode::AddChild(string data)
{
    ASTNode* newNode = new ASTNode;
    newNode->data = data;
    children.push_back(newNode);
}


void ASTNode::PrintChildren(ASTNode node) {
    for (int i = 0; i < node.children.size(); i++) {
        cout << "   " << node.children[i]->data;
    }
}
