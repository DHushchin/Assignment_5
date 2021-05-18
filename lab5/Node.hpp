#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Type {
    Variable,
    Number,
    MathOperator,
    UNDEFINED
};

class Node
{
    vector<Node*> children;
    string data;
    Type type;
    Node* parent;
public:
    Node();
    vector<Node*> GetChildren();
    void AddChild(string);
    void PrintChildren();
    string GetData();
    Node* GetParent();
    void SetData(string value);
    void SetType(Type type);
    Type GetType();
    ~Node();
};


