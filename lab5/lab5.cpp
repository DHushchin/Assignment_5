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

class Node {
    Node* root;
    vector<Node*> children;
    string data;
    Type type;
public:
    Node();
    void AddChild(string);
    void PrintChildren();
    ~Node();
};

Node::Node()
{
    root = nullptr;
    root->type = Type::UNDEFINED;
    root->data = "";
}

void Node::PrintChildren()
{
    Node* temp;
    cout << "children: ";
    for (size_t i = 0; i < children.size(); i++)
    {
        temp = children[i];
        cout << *(temp).data << " ";
    }
}

void Node::AddChild(string data)
{
    Node* newNode = new Node;
    newNode->data = data;
    this->children.push_back(newNode);
}

Node::~Node()
{
    for (size_t i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

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

void InputData(map<string, double>& variables, string& problem);

int main(int argc, char* argv[]) {
    map<string, double> variables;
    string problem;
    Node node;
    node.AddChild("+");
    node.AddChild("-");
    node.AddChild("/");
    node.PrintChildren();
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
    this->left = nullptr;
    this->right = nullptr;
}

ASTNode::~ASTNode()
{
    delete left;
    delete right;
}