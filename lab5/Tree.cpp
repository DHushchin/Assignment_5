#include "Tree.hpp"


Tree::Tree() {
    tree.SetType(Type::UNDEFINED);
    problem = "";
    InputData();
    ShuntingYard SY(problem);
    rrpn = SY.getResult();
}


string Tree::getProblem() {
    return problem;
}


Node* Tree::getRoot() {
    return tree.GetChildren()[variables.size() + 1];
}


vector<pair<string, double>> Tree::getVariables() {
    return variables;
}


void Tree::InputData() {
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
        if (!(str.find('*') != -1 || str.find('-') != -1 || str.find('+') != -1 || str.find('^') != -1 || str.find('/') != -1) && !(str.find('?') != -1 && str.find(':') != -1))
        {
            pair<string, double> curr;
            string temp;
            temp = str.substr(0, str.find('=') - 1);
            curr.first = temp;
            temp = str.substr(str.find('=') + 2, str.size() - str.find('=') - 3);
            curr.second = stof(temp);
            variables.push_back(curr);
        }
        else if (str.find('?') != -1 && str.find(':') != -1)
        {
            ternary.push(str.substr(str.find(':') + 1, str.size() - str.find(':') - 2));
            str.erase(str.find(':'), str.size() - str.find(':') + 1);

            ternary.push(str.substr(str.find('?') + 1, str.size() - str.find('?')));
            str.erase(str.find('?'), str.size() - str.find('?') + 1);

            ternary.push(str.substr(str.find('=') + 1, str.size() - str.find('=')));
            str.erase(str.find('='), str.size() - str.find('=') + 1);


            ternary.push(str);
            str.clear();
            ternary.push("==");
        }
        else
        {
            problem = str.substr(0, str.size() - 1);
        }
    }
    input.close();
}


void Tree::BuildTree() {
    for (size_t i = 0; i < variables.size(); i++) // строим "="
    {
        tree.AddChild("=");
        vector<Node*> temp = tree.GetChildren();
        temp[i]->AddChild(variables[i].first);
        temp[i]->AddChild(to_string(variables[i].second));
    }

    tree.AddChild(ternary.top());
    ternary.pop();

    while (!ternary.empty())
    {
        vector<Node*> tempvec = tree.GetChildren()[tree.GetChildren().size() - 1]->GetChildren();
        tree.GetChildren()[tree.GetChildren().size() - 1]->AddChild(ternary.top());
        ternary.pop();
    }

    tree.AddChild(rrpn.top());// первый знак
    rrpn.pop();
    vector<Node*> temp = tree.GetChildren();
    temp = tree.GetChildren();
    Node* start = temp[temp.size() - 1];

    while (!rrpn.empty()) // строим пример
    {
        temp = start->GetChildren();
        vector<Node*> secondtemp;

        if (temp.size() == 2)
        {
            if (temp[1]->GetType() == Type::MathOperator)
            {
                start = temp[1];
                continue;
            }
            start = start->GetParent();
            if (start->GetType() == Type::UNDEFINED)
                break;
        }
        else if (temp.size() == 1)
        {
            secondtemp = temp[0]->GetChildren();
            if (temp[0]->GetType() == Type::MathOperator && secondtemp.empty())
            {
                start = temp[0];
                start->AddChild(rrpn.top());
                rrpn.pop();
            }
            else
            {
                start->AddChild(rrpn.top());
                rrpn.pop();
            }
        }
        else if (temp.size() == 0)
        {
            start->AddChild(rrpn.top());
            rrpn.pop();
        }
    }
}


void Tree::ProcessTernary()
{
    vector<Node*> temp = tree.GetChildren();
    temp = temp[temp.size() - 2]->GetChildren();
    if (GetVariable(temp[1]->GetData()))
        SetVariable(temp[0]->GetData(), stod(temp[2]->GetData()));
    else
        SetVariable(temp[0]->GetData(), stod(temp[3]->GetData()));
}


void Tree::SetVariable(string name, double value)
{
    vector<Node*> temp = tree.GetChildren();
    for (size_t i = 0; i < temp.size() - 1; i++)
        if (temp[i]->GetData() == "=" && temp[i]->GetChildren()[0]->GetData() == name)
                temp[i]->GetChildren()[1]->SetData(to_string(value));
}


double Tree::GetVariable(string name)
{
    double res;
    vector<Node*> temp = tree.GetChildren();
    for (size_t i = 0; i < temp.size() - 1; i++)
        if (temp[i]->GetData() == "=" && temp[i]->GetChildren()[0]->GetData() == name) {
            res = stod(temp[i]->GetChildren()[1]->GetData());
            break;
        }
    return res;
}


double Tree::Evaluation(Node* node)
{
    string rootData = node->GetData();
    double res;
    if (getType(rootData) == Type::Number)
        res = stod(rootData);
    else if (getType(rootData) == Type::Variable)
        res = GetVariable(rootData);
    else
    {
        Node* left = node->GetChildren()[0];
        Node* right = node->GetChildren()[1];
        double op1 = Evaluation(left);
        double op2 = Evaluation(right);

        if (rootData == "+") { res = op1 + op2; }
        else if (rootData == "-") { res = op2 - op1; }
        else if (rootData == "*") { res = op1 * op2; }
        else if (rootData == "/") { res = op2 / op1; }
    }
    return res;
}


Type Tree::getType(string str) {
    if (str == "+" || str == "-" || str == "*" || str == "/")
        return Type::MathOperator;
    if (str[0] >= 48 && str[str.size() - 1] <= 57)
        return Type::Number;
    if (str[0] >= 65 && str[str.size() - 1] <= 122)
        return Type::Variable;
    return Type::UNDEFINED;
}