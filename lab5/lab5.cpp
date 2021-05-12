#include "Header.h"
#include "Node.h"

int main(int argc, char* argv[]) {
    vector<pair<string, double>> variables;
    string problem;
    InputData(variables, problem);
    BuildTree(variables, problem);
    system("pause");
    return 0;
}

void BuildTree(vector<pair<string, double>>& variables, string problem)
{
    Node tree;
    size_t i;
    for (i = 0; i < variables.size(); i++) // строим "="
    {
        tree.AddChild("=");
        vector<Node*> temp = tree.GetChildren();
        string str = variables[i].first;
        temp[i]->AddChild(str);
        str = variables[i].second;
        temp[i]->AddChild(str);
    }
    vector<pair<int, vector<int>>> data = Data(problem);
}

vector<pair<int, vector<int>>> Data(string problem)
{
    // ^ () *,/, +,-
    vector<pair<int, vector<int>>> data;
    CountOperations(data, problem, '^');
    CountOperations(data, problem, '(');
    CountOperations(data, problem, ')');
    CountOperations(data, problem, '*');
    CountOperations(data, problem, '/');
    CountOperations(data, problem, '+');
    CountOperations(data, problem, '-');
    return data;
}

void CountOperations(vector<pair<int, vector<int>>> &data, string problem, char a)
{
    pair<int, vector<int>> temp;
    int start = 0;
    int counter = 0;
    while (start != -1)
    {
        start = problem.find(a, start);
        temp.second.push_back(start);
        counter++;
    }
    temp.first = counter;
    data.push_back(temp);
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
