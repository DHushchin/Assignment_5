#include "Header.h"
#include "Node.h"

void BuildTree(Node*, vector<pair<string, double>>&, stack<string>);
float Evaluation(Node* ast, Node* root);
Type gettype(string str);
double GetVariable(Node* root, string name);

int main(int argc, char* argv[]) {
    vector<pair<string, double>> variables;
    string problem;
    InputData(variables, problem);
    stack<string> rrpn = ShuntingYard(problem);
    Node tree;
    BuildTree(&tree, variables, rrpn);
    vector<Node*> temp;
    temp = tree.GetChildren();
    Node* root = temp[variables.size()];
    double result = Evaluation(&tree, root);
    cout << result;
    system("pause");
    return 0;
}

void BuildTree(Node* tree, vector<pair<string, double>>& variables, stack<string> rrpn)
{
    tree->SetType(Type::UNDEFINED);
    size_t i;
    for (i = 0; i < variables.size(); i++) // строим "="
    {
        tree->AddChild("=");
        vector<Node*> temp = tree->GetChildren();
        string str = variables[i].first;
        temp[i]->AddChild(str);
        str = to_string(variables[i].second);
        temp[i]->AddChild(str);
    }

    
    tree->AddChild(rrpn.top());// первый знак
    rrpn.pop();
    vector<Node*> temp = tree->GetChildren();
    temp = tree->GetChildren();
    Node* start = temp[2];


    while (!rrpn.empty()) // строим пример
    {
        temp = start->GetChildren();
        vector<Node*> secondtemp;

        if (temp.size() == 2 /*&& !secondtemp.empty()*/)
        {
            if (temp[1]->GetType() == Type::MathOperator)
            {
                start = temp[1];
                continue;
            }
            start = start->GetParent();
            if (start->GetType() == Type::UNDEFINED)
            {
                break;
            }
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
            else //(temp[0]->GetType() == Type::Variable || temp[0]->GetType() == Type::Number)
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

double GetVariable(Node* ast, string name)
{
    vector<Node*> temp = ast->GetChildren();
    for (size_t i = 0; i < temp.size()-1; i++)
    {
        if (temp[i]->GetData() == "=")
        {
            
            if (temp[i]->GetChildren()[0]->GetData() == name)
            {
                return stof(temp[i]->GetChildren()[1]->GetData());
            }
        }
    }
}

float Evaluation(Node* ast, Node* root)
{
    string s = root->GetData();

    if (gettype(s) == Type::Number)
    {
        return stof(s);
    }
    else if (gettype(s) == Type::Variable)
    {
        return GetVariable(ast, s);
    }
    else
    {
        Node* left = (root->GetChildren())[0];
        float op1 = Evaluation(ast, left);
        Node* right = (root->GetChildren())[1];
        float op2 = Evaluation(ast, right);

        if (s == "+") { return op1 + op2; }
        else if (s == "-") { return op1 - op2; }
        else if (s == "*") { return op1 * op2; }
        else if (s == "/") { return op1 / op2; }
    }
}

Type gettype(string str) {
    if (str == "+" || str == "-" || str == "*" || str == "/")
        return Type::MathOperator;
    if (str[0] >= 48 && str[str.size() - 1] <= 57)
    {
        return Type::Number;
    }
    if (str[0] >= 41 && str[str.size() - 1] <= 122)
    {
        return Type::Variable;
    }
    return Type::UNDEFINED;
}

void InputData(vector<pair<string, double>>& variables, string& problem)
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
            variables.push_back(curr);
        }
        else
        {
            problem = str.substr(0, str.size() - 1);
        }
    }
    input.close();
}
