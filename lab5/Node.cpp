#include "Node.hpp"

using namespace std;

Node::Node()
{
    type = Type::UNDEFINED;
    parent = nullptr;
}


vector<Node*> Node::GetChildren()
{
    return children;
}


void Node::PrintChildren()
{
    cout << "Children: ";
    for (size_t i = 0; i < children.size(); i++)
        cout << children[i]->data << "  ";
}


string Node::GetData()
{
    return data;
}


Node* Node::GetParent()
{
    return parent;
}


void Node::SetType(Type type)
{
    this->type = type;
}


void Node::SetData(string value)
{
    data = value;
}


void Node::AddChild(string data)
{
    Node* newNode = new Node;
    newNode->data = data;
    if (data == "+" || data == "-" || data == "^" || data == "*" || data == "/")
        newNode->type = Type::MathOperator;
    else if ((int)data[0] >= 48 && (int)data[0] <= 57)
        newNode->type = Type::Number;
    else if (((int)data[0] >= 65 && (int)data[0] <= 90) || ((int)data[0] >= 97 && (int)data[0] <= 122))
        newNode->type = Type::Variable;
    this->children.push_back(newNode);
    newNode->parent = this;
}


Type Node::GetType()
{
    return type;
}


Node::~Node()
{
    for (size_t i = 0; i < children.size(); i++)
        delete children[i];
}