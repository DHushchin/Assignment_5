#pragma once
#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int capacity;
    int size;
public:
    Stack();
    Stack(int size);
    Stack(const Stack& other);
    ~Stack();
    void push(int x);
    void pop();
    bool empty();
    int top();
};
