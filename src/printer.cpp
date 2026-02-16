#include "calculator.hpp"

#include <stdio.h>

static void printResult(const CalcContext* ctx)
{
    if (ctx->operation == '!')
    {
        printf("%lld! = %lld\n", ctx->first, ctx->result);
    }
    else
    {
        printf("%lld %c %lld = %lld\n", ctx->first, ctx->operation, ctx->second, ctx->result);
    }
}

static void printAppStatus(const CalcContext* ctx)
{
    switch (ctx->appStatus)
    {
    case AppStatus::ERROR_PARSE:
        printf("Error: Failed to parse arguments. Use --help for usage info.\n");
        break;
    case AppStatus::ERROR_VALIDATION:
        printf("Error: Validation failed. Check your arguments.\n");
        break;
    case AppStatus::ERROR_MATH:
        break;
    case AppStatus::ERROR_HELP:
        printf("Console calculator\n");
        printf("Usage: calculator --first [num] --second [num]  --op [operation]\n");
        printf("Operations: + (add), - (sub), * (mul), / (div), ^ (pow), ! (factorial)\n");
        break;
    default:
        printf("Error: An unknown app error occurred (code: %d).\n", (int)ctx->appStatus);
        break;
    }
}

static void printMathStatus(const CalcContext* ctx)
{
    switch (ctx->mathStatus)
    {
    case pvm_math_lib::MathStatus::DIVISION_BY_ZERO:
        printf("Error: Mathematical overflow.\n");
        break;
    case pvm_math_lib::MathStatus::OVERFLOW_ERROR:
        printf("Error: Division by zero.\n");
        break;
    case pvm_math_lib::MathStatus::INVALID_INPUT:
        printf("Error: Invalid argument for operation.\n");
        break;
    default:
        printf("Error: An unknown mathematical error occurred (code: %d).\n", (int)ctx->mathStatus);
        break;
    }
}

void print(CalcContext* ctx)
{
    if (ctx->appStatus != AppStatus::SUCCESS)
    {
        printAppStatus(ctx);
        return;
    }

    if (ctx->mathStatus != pvm_math_lib::MathStatus::OK)
    {
        printMathStatus(ctx);
        return;
    }

    printResult(ctx);

    return;
}
