#include "Header.h"
#include "Node.h"

bool check = false;
void BuildTree(Node* tree, vector<pair<string, double>>& variables, stack<string> rrpn, stack<string>& ternary);
double Evaluation(Node* ast, Node* root);
Type gettype(string str);
double GetVariable(Node* root, string name);
void ProcessTernary(Node* ast);
void SetVariable(Node* ast, string name, double value);

int main(int argc, char* argv[]) {
    vector<pair<string, double>> variables;
    string problem;
    stack<string> ternary;
    InputData(variables, problem, ternary);
    stack<string> rrpn = ShuntingYard(problem);
    Node tree;
    BuildTree(&tree, variables, rrpn, ternary);
    vector<Node*> temp;
    ProcessTernary(&tree);
    temp = tree.GetChildren();
    Node* root = temp[variables.size()+1];
    double result = Evaluation(&tree, root);
    cout << "problem: " << problem << endl;
    cout << "result = " << result << endl;
    system("pause");
    return 0;
}

void BuildTree(Node* tree, vector<pair<string, double>>& variables, stack<string> rrpn, stack<string>& ternary)
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

    tree->AddChild(ternary.top());
    ternary.pop();
    while (!ternary.empty())
    {
        string temp;
        vector<Node*> tempvec;
        tempvec = tree->GetChildren()[tree->GetChildren().size() - 1]->GetChildren();
        tree->GetChildren()[tree->GetChildren().size() - 1]->AddChild(ternary.top());
        ternary.pop();
    }
    
    tree->AddChild(rrpn.top());// первый знак
    rrpn.pop();
    vector<Node*> temp = tree->GetChildren();
    temp = tree->GetChildren();
    Node* start = temp[temp.size()-1];


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

double GetVariable(Node* ast, string name)
{
    vector<Node*> temp = ast->GetChildren();
    for (size_t i = 0; i < temp.size() - 1; i++)
    {
        if (temp[i]->GetData() == "=")
        {

            if (temp[i]->GetChildren()[0]->GetData() == name)
            {
                return stod(temp[i]->GetChildren()[1]->GetData());
            }
        }
    }
}

void ProcessTernary(Node* ast)
{
    vector<Node*> temp = ast->GetChildren();
    temp = temp[temp.size() - 2]->GetChildren();
    string name = temp[1]->GetData();
    if (GetVariable(ast, name) != 0)
    {
        SetVariable(ast, temp[0]->GetData(), stod(temp[2]->GetData()));
    }
    else
    {
        SetVariable(ast, temp[0]->GetData(), stod(temp[3]->GetData()));
    }
}

void SetVariable(Node* ast, string name, double value)
{
    vector<Node*> temp = ast->GetChildren();
    for (size_t i = 0; i < temp.size() - 1; i++)
    {
        if (temp[i]->GetData() == "=")
        {
            if (temp[i]->GetChildren()[0]->GetData() == name)
            {
                temp[i]->GetChildren()[1]->SetData(to_string(value));
            }
        }
    }
}

double Evaluation(Node* ast, Node* root)
{
    string s = root->GetData();

    if (gettype(s) == Type::Number)
    {
        return stod(s);
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
        else if (s == "-") { return op2 - op1; }
        else if (s == "*") { return op1 * op2; }
        else if (s == "/") { return op2 / op1; }
    }
}


Type gettype(string str) {
    if (str == "+" || str == "-" || str == "*" || str == "/")
        return Type::MathOperator;
    if (str[0] >= 48 && str[str.size() - 1] <= 57)
    {
        return Type::Number;
    }
    if (str[0] >= 65 && str[str.size() - 1] <= 122)
    {
        return Type::Variable;
    }
    return Type::UNDEFINED;
}

void InputData(vector<pair<string, double>>& variables, string& problem, stack<string>& ternary)
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
            ternary.push(str.substr(str.find(':')+1, str.size()-str.find(':')-2));
            str.erase(str.find(':'), str.size() - str.find(':')+1);

            ternary.push(str.substr(str.find('?')+1, str.size() - str.find('?')));
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
