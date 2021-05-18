#include "Tree.hpp"


int main(int argc, char* argv[]) {
    Tree AST;
    AST.BuildTree();
    AST.ProcessTernary();
    Node* root = AST.getRoot();
    cout << "problem: " << AST.getProblem() << endl;
    cout << "result: " << AST.Evaluation(root) << endl;
    system("pause");
    return 0;
}