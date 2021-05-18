#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
const int SIZE = 1;

using namespace std;


template <typename T>
class Stack
{
    T* arr;
    int top;
    int _size;
public:
    Stack(int size = SIZE);// Stack(int size = 0);
    ~Stack();
    void push(T);
    T pop();
    T back();
    void append(int);
    int size();
    bool isEmpty();
    bool isFull();
    friend string pushOperator(string example, string postfix, Stack* operationsStack, int index);//check for need
};


class ShuntingYard {
private:
    Stack<string> operationsStack; //stack with operations +-/*
    string polishNotation = " "; //polish notation version of string
    string problem;
    stack<string> result;
    int findOperator(string, int);
    int findOperatorRight(string);
    int skipSpaces(int);
    double getFirstNumber(int);
    double getSecondNumber(int);
    int priorityOfOperation(string);
    double doCalculation(float, float, string);
    string pushOperator(string example, string postfix, int index);
public:
    ShuntingYard();
    ShuntingYard(string problem);
    void setProblem(string problem);
    stack<string> getResult();
};