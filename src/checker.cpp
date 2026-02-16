#include "calculator.hpp"

static AppStatus validateOperationAndOperands(const CalcContext* ctx)
{
    AppStatus retStatus = AppStatus::SUCCESS;

    switch (ctx->operation)
    {
    case '+':
        break;
    case '-':
        break;
    case '*':
        break;
    case '/':
        if (ctx->second == 0)
        {
            retStatus = AppStatus::ERROR_VALIDATION;
        }
        break;
    case '^':
        if (ctx->second < 0)
        {
            retStatus = AppStatus::ERROR_VALIDATION;
        }
        break;
    case '!':
        if (ctx->first < 0)
        {
            retStatus = AppStatus::ERROR_VALIDATION;
        }
        break;
    default:
        retStatus = AppStatus::ERROR_VALIDATION;
        break;
    }

    return retStatus;
}

void check(CalcContext* ctx)
{
    if (ctx->appStatus != AppStatus::SUCCESS)
    {
        return;
    }

    if (ctx->operation == '\0' || ctx->operation == ' ')
    {
        ctx->appStatus = AppStatus::ERROR_VALIDATION;
        return;
    }

    if ((ctx->appStatus = validateOperationAndOperands(ctx)) != AppStatus::SUCCESS)
    {
        return;
    }
}
