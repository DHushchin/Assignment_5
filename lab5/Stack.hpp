#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Stack {
private:
    vector<T> elements;
public:
    void push(T const&);
    void pop();
    T top();
    bool empty();
};
