#pragma once


#include "Node.hpp"
#include "ShuntingYard.hpp"
#include <fstream>


class Tree {
private:
    Node tree;
    string problem;
    vector<pair<string, double>> variables;
    stack<string> ternary, rrpn;
public:
    Tree();
    string getProblem();
    Node* getRoot();
    vector<pair<string, double>> getVariables();
    void InputData();
    void BuildTree();
    void ProcessTernary();
    void SetVariable(string name, double value);
    double GetVariable(string name);
    double Evaluation(Node* node);
    Type getType(string str);
};





