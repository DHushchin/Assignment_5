#pragma once
#include "Header.h"
class Node
{
    vector<Node*> children;
    string data;
    Type type;
    Node* parent;
public:
    Node();
    vector<Node*> GetChildren();
    Type GetType()
    {
        return type;
    }
    void AddChild(string);
    void PrintChildren();
    string GetData();
    Node* GetParent();
    void SetType(Type type);
    ~Node();
};


