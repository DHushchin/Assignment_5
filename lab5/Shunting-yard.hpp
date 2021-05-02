#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

const int SIZE = 1;

using namespace std;

void ShuntingYard(int argc, char* argv[]);

int findOperator(string, int);
int findOperatorRight(string);
int skipSpaces(string, int);
float getFirstNumber(string, int);
float getSecondNumber(string, int);
int priorityOfOperation(string);
float doCalculation(float, float, string);

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