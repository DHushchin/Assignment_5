#pragma once
#include "ShuntingYard.hpp"


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


ShuntingYard::ShuntingYard() {

}


ShuntingYard::ShuntingYard(string problem)
{
    polishNotation = " ";
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
            if (str[i] == '-' && i == 0) 
                str[i] = 'm';
            else if (str[i] == '-' && i != 0) 
                if (str[i - 1] == '(' || str[i - 1] == '*' || str[i - 1] == '/') 
                    str[i] = 'm';
        }

        if (str.length() == 1) {
            if (isdigit(str[0]))
                polishNotation = polishNotation + str + ' ';
            else
                polishNotation = pushOperator(str, polishNotation, 0);/////push             
        }
        else 
        {
            int start = 0;
            int operationIndex = findOperator(str, start);
            if (operationIndex < 0) polishNotation = polishNotation + str + ' '; // 22
            else {
                while (operationIndex >= 0) {
                    if (operationIndex == str.length() - 1)
                    {
                        polishNotation = polishNotation + str.substr(start, operationIndex - start) + ' ';
                        polishNotation = pushOperator(str, polishNotation, operationIndex);/////push
                        operationIndex = -1;
                    }
                    else if (operationIndex == 0) {
                        polishNotation = pushOperator(str, polishNotation, operationIndex);/////push
                        start = operationIndex + 1;
                        operationIndex = findOperator(str, start);
                        if (operationIndex == -1) 
                            polishNotation = polishNotation + str.substr(start) + ' ';                       
                    }
                    else 
                    {
                        if (!(str.substr(start, operationIndex - start)).empty()) 
                            polishNotation = polishNotation + str.substr(start, operationIndex - start) + ' ';                       
                        polishNotation = pushOperator(str, polishNotation, operationIndex);/////push
                        start = operationIndex + 1;
                        operationIndex = findOperator(str, start);
                        if (operationIndex < 0) {
                            operationIndex = findOperatorRight(str);
                            polishNotation = polishNotation + str.substr(operationIndex + 1) + ' ';
                            operationIndex = -1;
                        }
                    }
                }
            }                            
        }
    }
    for (int i = 0; i < operationsStack.size();) 
        polishNotation = polishNotation + operationsStack.pop() + ' ';

    while (!polishNotation.empty())
    {
        if (polishNotation.substr(0, polishNotation.find(' ')) == "")
            polishNotation.erase(0, polishNotation.find(' ') + 1);
        else if (polishNotation.substr(0, polishNotation.find(' ')) != " ")
        {
            result.push(polishNotation.substr(0, polishNotation.find(' ')));
            polishNotation.erase(0, polishNotation.find(' ') + 1);
        }
        else
            polishNotation.erase((0, polishNotation.find(' ')));
    }
}


int ShuntingYard::findOperator(string str, int start) {
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


int ShuntingYard::findOperatorRight(string str) {
    int operationIndex1 = str.rfind('+');
    int operationIndex2 = str.rfind('-');
    int operationIndex3 = str.rfind('*');
    int operationIndex4 = str.rfind('/');
    int operationIndex5 = str.rfind('^');
    int operationIndex6 = str.rfind('(');
    int operationIndex7 = str.rfind(')');
    return max(operationIndex7, max(operationIndex6, max(operationIndex5, max(operationIndex4, (max(operationIndex3, (max(operationIndex1, operationIndex2))))))));
}


int ShuntingYard::priorityOfOperation(string operation)
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


string ShuntingYard::pushOperator(string example, string postfix, int index)
{
    string operationString = example.substr(index, 1);
    if (operationsStack.isEmpty())
        operationsStack.push(operationString);
    else
    {
        if (operationString[0] == '(') 
            operationsStack.push(operationString);
        else if (operationString[0] == ')') {
            while (operationsStack.back() != "(") 
                postfix = postfix + operationsStack.pop() + ' ';
            operationsStack.pop();
        }
        else if (priorityOfOperation(operationsStack.back()) >= priorityOfOperation(operationString))
        {
            postfix = postfix + operationsStack.pop() + ' ';
            operationsStack.push(operationString);
        }
        else
            operationsStack.push(operationString);
    }
    return postfix;
}


double ShuntingYard::getFirstNumber(int operationIndex) {
    int end = polishNotation.find(' ', operationIndex);
    double number;
    if (polishNotation.substr(operationIndex, end - operationIndex)[0] == 'm') {
        number = stod(polishNotation.substr(operationIndex + 1, end - operationIndex - 1)) * (-1);
    }
    else {
        number = stod(polishNotation.substr(operationIndex, end - operationIndex));
    }

    return number;
}


double ShuntingYard::getSecondNumber(int operationIndex) {
    int start = polishNotation.find(' ', operationIndex) + 1;
    int end = polishNotation.find(' ', start);
    double number;
    if (polishNotation.substr(start, end - start)[0] == 'm') {
        number = stod(polishNotation.substr(start + 1, end - start - 1)) * (-1);
    }
    else {
        number = stod(polishNotation.substr(start, end - start));
    }

    return number;
}


int ShuntingYard::skipSpaces(int operationIndex) {
    for (int i = 0; i < 3; i++) {
        operationIndex = polishNotation.rfind(' ', operationIndex) - 1;
    }
    operationIndex += 2;
    return operationIndex;
}


double ShuntingYard::doCalculation(float firstNum, float secondNum, string operation)
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


stack<string> ShuntingYard::getResult() {
    return result;
}
