#include "Node.h"
Node::Node()
{
    //children.resize(1);
    //children[0] = nullptr;
}

vector<Node*> Node::GetChildren()
{
    return children;
}

void Node::PrintChildren()
{
    Node* temp;
    cout << "children: ";
    for (size_t i = 0; i < children.size(); i++)
    {
        temp = children[i];
        cout << children[i]->data << " ";
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