#pragma once
#include "Header.h"
class Node
{
    vector<Node*> children;
    string data;
    Type type;
public:
    Node();
    vector<Node*> GetChildren();
    void AddChild(string);
    void PrintChildren();
    ~Node();
};


