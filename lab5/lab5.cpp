#include "Header.h"
#include "Node.h"

void BuildTree(Node*, vector<pair<string, double>>&, stack<string>);
void ShowTree(Node* root, int level);

int main(int argc, char* argv[]) {
    vector<pair<string, double>> variables;
    string problem;
    InputData(variables, problem);
    stack<string> rrpn = ShuntingYard(problem);
    Node tree;
    BuildTree(&tree, variables, rrpn);

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

void ShowTree(Node* root, int level)
{
    vector<Node*> temp;
    if (root)
    {
        temp = root->GetChildren();
        if (!temp.empty())
        {
            ShowTree(temp[0], level + 1);
            for (int i = 0; i < level; i++) cout << "   ";
            cout << root->GetData() << endl;
        }
        ShowTree(temp[1], level + 1);
    }
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
