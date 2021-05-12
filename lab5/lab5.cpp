#include "Header.h"
#include "Node.h"

int main(int argc, char* argv[]) {
    map<string, double> variables;
    string problem;
    Node node;
    node.AddChild("+");
    node.AddChild("-");
    node.AddChild("/");
    vector<Node*> temp;
    temp = node.GetChildren();
    temp[0]->AddChild("1");
    temp[0]->AddChild("2");
    temp[0]->PrintChildren();
    InputData(variables, problem);
    system("pause");
    return 0;
}

void BuildTree()

void InputData(map<string, double> &variables, string& problem)
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
            variables.insert(curr);
        }
        else
        {
            problem = str.substr(0, str.size() - 1);
        }
    }
    input.close();
}
