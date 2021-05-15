#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Shunting-yard.hpp"
#include <fstream>
#include <map>
#include <utility>

using namespace std;
void InputData(vector<pair<string, double>>& variables, string& problem);

enum class MathOperator {
    plus,
    minus,
    multiply,
    divide,
    assign
};

enum class CompareOperator {
    equal,
    not_equal,
    more,
    more_or_equal,
    less,
    less_or_equal
};

enum class Type {
    Variable,
    Number,
    MathOperator,
    CompareOperator,
    UNDEFINED
};
