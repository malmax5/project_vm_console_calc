#pragma once

#include <pvm_math_lib/calculator_math.hpp>

enum class AppStatus
{
    SUCCESS = 0,
    ERROR_PARSE = 1,
    ERROR_VALIDATION = 2,
    ERROR_MATH = 3,
    ERROR_HELP = 4
};

struct CalcContext
{
    long long first;
    long long second;
    char operation;
    long long result;
    pvm_math_lib::MathStatus mathStatus;
    AppStatus appStatus;
};

// TODO
void run();
void parse(CalcContext* ctx, int argc, char** argv);
// void check(CalcContext* ctx,);
void calculate(CalcContext* ctx);
// void print(CalcContext* ctx);
