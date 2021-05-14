#pragma once
#include "Shunting-yard.hpp"


template <typename T>
Stack<T>::Stack(int size)
{
    arr = new T[size];
    _size = size;
    top = -1;
}

template <typename T>
void Stack<T>::append(int size)
{
    T* newArr = new T[size + _size];
    for (int i = 0; i < _size; i++)
        newArr[i] = arr[i];
    _size += size;
    arr = newArr;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template <typename T>
void Stack<T>::push(T x)
{
    if (isFull())
    {
        if (!isEmpty())append(2);
        else append(_size);
    }
    arr[++top] = x;
}

template <typename T>
T Stack<T>::pop()
{
    if (isEmpty())
    {
        throw out_of_range("Error: stack is empty");
    }
    return arr[top--];
}

template <typename T>
T Stack<T>::back()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        throw out_of_range("Error: stack is empty");
    }
}

template <typename T>
int Stack<T>::size() {
    return top + 1;
}

template <typename T>
bool Stack<T>::isEmpty() {
    return top == -1;
}

template <typename T>
bool Stack<T>::isFull() {
    return top == _size - 1;
}


stack<string> ShuntingYard(string problem)
{
    Stack<string> operationsStack;//stack with operations +-/*
    string polishNotation = " ";//polish notation version of string
    //1+2+ 3 +4 + 5
    int argc = 0;
    int start = 0;
    vector<string> argv;
    while (problem.size() != 0)
    {
        if (problem.find(' ') == -1)
        {
            argv.push_back(problem.substr(0, problem.size()));
            problem.erase(0, problem.size());
        }
        else
        {
            argv.push_back(problem.substr(0, ' '));
            problem.erase(0, problem.find(' ') + 1);
        }
    }
    for (int i = 0; i < argv.size(); i++) {
        string str = argv[i];
        size_t index = 0;
        while ((index = str.find(' ')) != string::npos) str.erase(index, 1);
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '-' && i == 0) {
                str[i] = 'm';
            }
            else if (str[i] == '-' && i != 0) {
                if (str[i - 1] == '(' || str[i - 1] == '*' || str[i - 1] == '/') {
                    str[i] = 'm';
                }
            }
        }

        if (str.length() == 1) {
            if (isdigit(str[0])) {
                polishNotation = polishNotation + str + ' ';
            }
            else
                polishNotation = pushOperator(str, polishNotation, &operationsStack, 0);/////push               
        }
        else {
            int start = 0;
            int operationIndex = findOperator(str, start);
            if (operationIndex < 0) polishNotation = polishNotation + str + ' '; // 22
            else {
                while (operationIndex >= 0) {


                    if (operationIndex == str.length() - 1)
                    {
                        polishNotation = polishNotation + str.substr(start, operationIndex - start) + ' ';


                        polishNotation = pushOperator(str, polishNotation, &operationsStack, operationIndex);/////push

                        operationIndex = -1;
                    }
                    else if (operationIndex == 0) {


                        polishNotation = pushOperator(str, polishNotation, &operationsStack, operationIndex);/////push

                        start = operationIndex + 1;
                        operationIndex = findOperator(str, start);
                        if (operationIndex == -1) {
                            polishNotation = polishNotation + str.substr(start) + ' ';
                        }
                    }
                    else {
                        if (!(str.substr(start, operationIndex - start)).empty()) {
                            polishNotation = polishNotation + str.substr(start, operationIndex - start) + ' ';
                        }


                        polishNotation = pushOperator(str, polishNotation, &operationsStack, operationIndex);/////push

                        start = operationIndex + 1;
                        operationIndex = findOperator(str, start);
                        if (operationIndex < 0) {
                            operationIndex = findOperatorRight(str);//12+34-7*2 12+34-7* ##+3
                            polishNotation = polishNotation + str.substr(operationIndex + 1) + ' ';
                            operationIndex = -1;
                        }
                    }
                }
            }                            // 12+34-7*2; +22-4; +22-; 12+
        }
    }
    for (int i = 0; i < operationsStack.size();) {
        polishNotation = polishNotation + operationsStack.pop() + ' ';
    }
    stack<string> result;
    while (!polishNotation.empty())
    {
        if (polishNotation.substr(0, polishNotation.find(' ')) == "")
        {
            polishNotation.erase(0, polishNotation.find(' ') + 1);
        }
        else if (polishNotation.substr(0, polishNotation.find(' ')) != " ")
        {
            result.push(polishNotation.substr(0, polishNotation.find(' ')));
            polishNotation.erase(0, polishNotation.find(' ') + 1);
        }

        else
        {
            polishNotation.erase((0, polishNotation.find(' ')));
        }
    }
    return result;
    /*float result;
    start = 0;
    float num1, num2;
    int operationIndex = findOperator(polishNotation, start);
    while (operationIndex > 0)
    {
        int numberIndex = skipSpaces(polishNotation, operationIndex);
        num1 = getFirstNumber(polishNotation, numberIndex);
        num2 = getSecondNumber(polishNotation, numberIndex);
        result = doCalculation(num1, num2, polishNotation.substr(operationIndex, 1));
        string resultStr = to_string(result);
        if (resultStr[0] == '-') {
            resultStr[0] = 'm';
        }
        polishNotation = polishNotation.replace(numberIndex, operationIndex + 1 - numberIndex, resultStr);
        operationIndex = findOperator(polishNotation, start);
    }
    for (int i = 0; i < polishNotation.length() / 2; i++)
    {
        if (polishNotation[i] == 'm') {
            polishNotation[i] = '-';
        }
    }
    cout << endl << "Result: " << fixed << setprecision(3) << stof(polishNotation);*/
}


int findOperator(string str, int start) {
    int operationIndex1 = str.find('+', start);
    int operationIndex2 = str.find('-', start);
    int operationIndex3 = str.find('*', start);
    int operationIndex4 = str.find('/', start);
    int operationIndex5 = str.find('^', start);
    int operationIndex6 = str.find('(', start);
    int operationIndex7 = str.find(')', start);
    for (int i = 0; i < str.length(); i++) {
        if (operationIndex1 == i) return operationIndex1;
        else if (operationIndex2 == i) return operationIndex2;
        else if (operationIndex3 == i) return operationIndex3;
        else if (operationIndex4 == i) return operationIndex4;
        else if (operationIndex5 == i) return operationIndex5;
        else if (operationIndex6 == i) return operationIndex6;
        else if (operationIndex7 == i) return operationIndex7;
    }
    return -1;
}

int findOperatorRight(string str) {
    int operationIndex1 = str.rfind('+');
    int operationIndex2 = str.rfind('-');
    int operationIndex3 = str.rfind('*');
    int operationIndex4 = str.rfind('/');
    int operationIndex5 = str.rfind('^');
    int operationIndex6 = str.rfind('(');
    int operationIndex7 = str.rfind(')');
    return max(operationIndex7, max(operationIndex6, max(operationIndex5, max(operationIndex4, (max(operationIndex3, (max(operationIndex1, operationIndex2))))))));
}

int priorityOfOperation(string operation)
{
    switch (operation[0])
    {
    case '(':
    case ')':
        return 0;
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}

string pushOperator(string example, string postfix, Stack<string>* operationsStack, int index)
{
    string operationString = example.substr(index, 1);
    if ((*operationsStack).isEmpty())
        (*operationsStack).push(operationString);
    else
    {
        if (operationString[0] == '(') {
            (*operationsStack).push(operationString);
        }
        else if (operationString[0] == ')') {

            while ((*operationsStack).back() != "(") {
                postfix = postfix + (*operationsStack).pop() + ' ';
            }
            (*operationsStack).pop();
        }
        else if (priorityOfOperation(((*operationsStack).back())) >= priorityOfOperation(operationString))
        {
            postfix = postfix + (*operationsStack).pop() + ' ';
            (*operationsStack).push(operationString);
        }
        else
            (*operationsStack).push(operationString);
    }
    return postfix;
}

float getFirstNumber(string polishNotation, int operationIndex) {
    int end = polishNotation.find(' ', operationIndex);
    float number;
    if (polishNotation.substr(operationIndex, end - operationIndex)[0] == 'm') {
        number = stof(polishNotation.substr(operationIndex + 1, end - operationIndex - 1)) * (-1);
    }
    else {
        number = stof(polishNotation.substr(operationIndex, end - operationIndex));
    }

    return number;
}
float getSecondNumber(string polishNotation, int operationIndex) {
    int start = polishNotation.find(' ', operationIndex) + 1;
    int end = polishNotation.find(' ', start);
    float number;
    if (polishNotation.substr(start, end - start)[0] == 'm') {
        number = stof(polishNotation.substr(start + 1, end - start - 1)) * (-1);
    }
    else {
        number = stof(polishNotation.substr(start, end - start));
    }

    return number;
}

int skipSpaces(string polishNotation, int operationIndex) {
    for (int i = 0; i < 3; i++) {
        operationIndex = polishNotation.rfind(' ', operationIndex) - 1;
    }
    operationIndex += 2;
    return operationIndex;
}

float doCalculation(float firstNum, float secondNum, string operation)
{
    switch (operation[0])
    {
    case '+':
        return firstNum + secondNum;
    case '-':
        return firstNum - secondNum;
    case '*':
        return firstNum * secondNum;
    case '/':
        return firstNum / secondNum;
    case '^':
        return pow(firstNum, secondNum);
    default:
        return -1;
    }
}
